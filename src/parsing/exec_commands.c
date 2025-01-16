/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 13:30:27 by jaimesan          #+#    #+#             */
/*   Updated: 2025/01/16 11:24:42 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_commands(t_mini *mini)
{
	t_token	*token;

	if (!mini->commands)
		return ;
	init_fds(mini);
	token = *mini->commands;
	if (token && !token->next && token->is_builtin)
		return (set_in_out_file(mini, token), builtin_commands(mini, token));
	while (token)
	{
		if (!token->next)
			mini->is_last_cmd = 1;
		pipex(mini, token);
		if (mini->prev_fd != -1 && mini->prev_fd != STDIN_FILENO
			&& mini->prev_fd != mini->fd[0])
			close(mini->prev_fd);
		mini->prev_fd = mini->fd[0];
		signal(SIGINT, &handle_sigint);
		token = token->next;
	}
	if (mini->prev_fd != -1 && mini->prev_fd != STDIN_FILENO)
		close(mini->prev_fd);
}

void	pipex(t_mini *mini, t_token *token)
{
	if (!mini->is_last_cmd)
		if (pipe(mini->fd) == -1)
			return (exit(EXIT_FAILURE), perror("Pipe Error"));
	mini->pid = fork();
	if (mini->pid == -1)
		return (exit(EXIT_FAILURE), perror("Fork Error"));
	if (mini->pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		set_in_out_file(mini, token);
		swap_fds(mini, token);
		execve_commands(mini, token);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		if (!mini->is_last_cmd)
			close(mini->fd[1]);
		waitpid(mini->pid, &g_status, 0);
		exit_codes();
	}
}

void	swap_fds(t_mini *mini, t_token *token)
{
	if (token->input_redir)
	{
		if (dup2(mini->infile, STDIN_FILENO) == -1)
			return (exit(EXIT_FAILURE), perror("dup2 input error."));
	}
	else if (mini->prev_fd != -1 && mini->prev_fd != STDIN_FILENO)
	{
		if (dup2(mini->prev_fd, STDIN_FILENO) == -1)
			return (exit(EXIT_FAILURE), perror("dup2 input error."));
	}
	if (token->output_redir)
	{
		if (dup2(mini->outfile, STDOUT_FILENO) == -1)
			return (exit(EXIT_FAILURE), perror("dup2 output error."));
	}
	else if (!mini->is_last_cmd)
	{
		if (dup2(mini->fd[1], STDOUT_FILENO) == -1)
			return (exit(EXIT_FAILURE), perror("dup2 output error."));
	}
	close_fds(mini);
}

void	execve_commands(t_mini *mini, t_token *token)
{
	if (token->is_builtin)
	{
		builtin_commands(mini, token);
		exit(g_status);
	}
	else if (!token->is_builtin)
	{
		if (execve(token->path, token->cmd, mini->env) == -1)
		{
			write(2, token->cmd[0], ft_strlen(token->cmd[0]));
			write(2, ": command not found.\n", 22);
			g_status = 127;
			exit(EXIT_SUCCESS);
		}
	}
}
