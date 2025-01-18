/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 13:30:27 by jaimesan          #+#    #+#             */
/*   Updated: 2025/01/16 16:27:52 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_commands(t_mini *mini)
{
	int     pipes[mini->pipes_i][2];
	pid_t   pids[mini->cmd_count];
	t_token		*token;
	int			i;

	if (!mini->commands)
		return ;
	token = *mini->commands;
	if (mini->cmd_count == 1 && is_builtin(token->cmd[0]))
		return (set_redirections(mini, token), builtin_commands(mini, token));
	i = 0;
	while (i < mini->pipes_i)
	{
		if (pipe(pipes[i++]) == -1)
			return (perror("Pipe Error"), exit(EXIT_FAILURE));
	}
	fork_commands(mini, token, pipes, pids);
	close_pipes(mini, token, pipes, 1);
	exit_codes();
	i = 0;
	while (i < mini->cmd_count)
		waitpid(pids[i++], &g_status, 0);
}

void	fork_commands(t_mini *mini, t_token *token, int pipes[][2], pid_t pids[])
{
	mini->i = 0;
	while (token)
	{
		pids[mini->i] = fork();
		if (pids[mini->i] == -1)
			return (exit(EXIT_FAILURE), perror("Fork Error"));
		if (pids[mini->i] == 0)
		{
			signal(SIGINT, SIG_DFL);
			set_redirections(mini, token);
			child_processing(mini, token, pipes);
			execve_commands(mini, token);
		}
		else
		{
			signal(SIGINT, &handle_sigint);
			signal(SIGINT, SIG_IGN);
			if (mini->i > 0)
				close(pipes[mini->i - 1][0]);
			if (mini->i < mini->pipes_i)
				close(pipes[mini->i][1]);
		}
		token = token->next;
		mini->i++;
	}
}

void	child_processing(t_mini *mini, t_token *token, int pipes[][2])
{
	if (token->input_redir)
	{
		if (dup2(mini->infile, STDIN_FILENO) == -1)
		{
			perror("dup2 input error");
			exit(EXIT_FAILURE);
		}
	}
	else if (mini->i > 0)
	{
		if (dup2(pipes[mini->i - 1][0], STDIN_FILENO) == -1)
		{
			perror("dup2 input error");
			exit(EXIT_FAILURE);
		}
	}
	if (token->output_redir)
	{
		if (dup2(mini->outfile, STDOUT_FILENO) == -1)
			return (perror("dup2 output error"), exit(EXIT_FAILURE));
	}
	else if (mini->i < mini->cmd_count - 1)
		if (dup2(pipes[mini->i][1], STDOUT_FILENO) == -1)
			return (perror("dup2 output error"), exit(EXIT_FAILURE));
}

void	close_pipes(t_mini *mini, t_token *token, int pipes[][2], int mode)
{
	int		i;

	i = 0;
	if (mode == 1)
	{
		while (i < mini->pipes_i)
		{
			if (i != mini->i - 1 || token->input_redir)
				close(pipes[i][0]);
			if (i != mini->i || token->output_redir)
				close(pipes[i][1]);
			i++;
		}
		if (mini->infile)
			close(mini->infile);
		if (mini->outfile)
			close(mini->outfile);
		return ;
	}
	while (i < mini->pipes_i)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
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
			exit(g_status);
		}
	}
}



