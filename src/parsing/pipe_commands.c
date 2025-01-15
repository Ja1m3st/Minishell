/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 16:02:40 by jaimesan          #+#    #+#             */
/*   Updated: 2025/01/15 13:50:59 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipex(t_mini *mini, t_token *token)
{
	if (token->next && pipe(mini->fd) == -1)
		return (perror("Pipe Error\n"));
	mini->pid = fork();
	if (mini->pid == -1)
		return (perror("Fork error\n"));
	if (mini->pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		if (token->input_redir || token->output_redir)
			set_in_out_file(mini, token);
		swap_fds(mini, token);
		close_fds(mini, token, 1);
		execve_commands(mini, token);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		close_fds(mini, token, 1);
		exit_codes();
	}
}

void	close_fds(t_mini *mini, t_token *token, int mod)
{
	if (!mod)
	{
		if (token->next)
			close(mini->fd[0]);
		if (!mini->is_last_cmd)
			close(mini->fd[1]);
	}
	if (mod)
	{
		if (token->next)
			close(mini->fd[1]);
		if (mini->is_last_cmd)
			close(mini->fd[0]);
	}
}

int	swap_fds(t_mini *mini, t_token *token)
{
	if (token->input_redir)
	{
		if (dup2(mini->infile, STDIN_FILENO) == -1)
		{
			perror("dup2 error (input)");
			exit(EXIT_FAILURE);
		}
		close(mini->infile);
	}
	else if (!mini->is_first_cmd)
	{
		if (dup2(mini->fd[0], STDIN_FILENO) == -1)
		{
			perror("dup2 error (pipe input)");
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
			perror("dup2 error (output)");
			exit(EXIT_FAILURE);
		}
		close(mini->outfile);
	}
	else if (!mini->is_last_cmd)
	{
		if (dup2(mini->fd[1], STDOUT_FILENO) == -1)
		{
			perror("dup2 error (pipe output)");
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
		exit(0);
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
