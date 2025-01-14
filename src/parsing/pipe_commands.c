/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 16:02:40 by jaimesan          #+#    #+#             */
/*   Updated: 2025/01/14 16:15:20 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_status;

void	pipex(t_mini *mini, t_token *token)
{
	if (token->next && pipe(mini->fd) == -1)
		return (perror("Pipe Error\n"));
	mini->pid = fork();
	if (mini->pid == -1)
		return (perror("Fork error\n"));
	if (mini->pid == 0)
	{
		if (token->input_redir || token->output_redir)
			set_in_out_file(mini, token);
		swap_fds(mini, token);
		if (token->next)
			close(mini->fd[0]);
		if (!mini->is_last_cmd)
			close(mini->fd[1]);
		execve_commands(mini, token);
	}
	else
	{
		if (token->next)
			close(mini->fd[1]);
		if (mini->is_last_cmd)
			close(mini->fd[0]);
		exit_codes(mini, &mini->pid, &g_status);
	}
}

void	exit_codes(t_mini *mini, pid_t *pid, int *status)
{
	waitpid(*pid, status, 0);
	if (WIFEXITED(*status))
		mini->exit_code = WEXITSTATUS(*status);
	else if (WIFSIGNALED(*status))
		mini->exit_code = 128 + WTERMSIG(*status);
	else
		mini->exit_code = -1;
}

int	swap_fds(t_mini *mini, t_token *token)
{
	if (token->input_redir)
	{
		if (dup2(mini->infile, STDIN_FILENO) == -1)
		{
			perror("dup2 error (input)\n");
			exit(EXIT_FAILURE);
		}
		close(mini->infile);
	}
	else if (!mini->is_first_cmd)
	{
		if (dup2(mini->fd[0], STDIN_FILENO) == -1)
		{
			perror("dup2 error (pipe input)\n");
			exit(EXIT_FAILURE);
		}
		close(mini->fd[0]);
	}
	return (swap_fds2(mini, token));
}

int	swap_fds2(t_mini *mini, t_token *token)
{
	if (token->output_redir)
	{
		if (dup2(mini->outfile, STDOUT_FILENO) == -1)
		{
			perror("dup2 error (output)\n");
			exit(EXIT_FAILURE);
		}
		close(mini->outfile);
	}
	else if (!mini->is_last_cmd)
	{
		if (dup2(mini->fd[1], STDOUT_FILENO) == -1)
		{
			perror("dup2 error (pipe output)\n");
			exit(EXIT_FAILURE);
		}
		close(mini->fd[1]);
	}
	return (execve_commands(mini, token));
}

int	execve_commands(t_mini *mini, t_token *token)
{
	if (token->is_builtin)
	{
		builtin_commands(mini, token);
		exit(EXIT_SUCCESS);
	}
	else if (!token->is_builtin)
	{
		if (execve(token->path, token->cmd, mini->env) == -1)
		{
			fprintf(stderr, "%s: command not found\n", token->cmd[0]);
			exit(127);
		}
	}
	return (0);
}
