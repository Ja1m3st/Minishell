/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 16:02:40 by jaimesan          #+#    #+#             */
/*   Updated: 2024/12/13 13:33:25 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipex(t_mini *mini, t_token *token)
{
	
	mini->pid = fork();
	if (mini->pid == -1)
		return (perror("Fork error\n"));
	if (mini->pid == 0)
	{
		if (token->input_redir || token->output_redir)
			set_in_out_file(mini, token);
		swap_fds(mini, token);
		close(mini->fd[0]);
		close(mini->fd[1]);
	}
	close(mini->fd[1]);
	mini->outfile = mini->fd[0];
	waitpid(mini->pid, NULL, 0);
}

int	swap_fds(t_mini *mini, t_token *token)
{
	if (token->input_redir)
	{
		if (dup2(mini->infile, STDIN_FILENO) == -1)
		{
			perror("dup2 error (input)\n");
			exit(EXIT_FAILURE);
			return (1);
		}
		close(mini->infile);
	}
	else if (!mini->is_first_cmd)
	{
		if (dup2(mini->fd[0], STDIN_FILENO) == -1)
		{
			perror("dup2 error (pipe input)\n");
			exit(EXIT_FAILURE);
			return (1);
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
			return (1);
		}
		close(mini->outfile);
	}
	else if (!mini->is_last_cmd)
	{
		if (dup2(mini->fd[1], STDOUT_FILENO) == -1)
		{
			perror("dup2 error (pipe output)\n");
			exit(EXIT_FAILURE);
			return (1);
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
		return (0);
	}
	else if (execve(token->path, token->cmd, mini->env) == -1)
	{
		perror("Failed to execute command\n");
		exit(EXIT_FAILURE);
		return (1);
	}
	return (0);
}
