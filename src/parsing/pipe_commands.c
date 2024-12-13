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
	if (pipe(mini->fd) == -1)
		return (perror("Pipe error\n"));
	mini->pid = fork();
	if (mini->pid == -1)
		return (perror("Fork error\n"));
	if (mini->pid == 0)
	{
		swap_fds(mini, token);
	}
	close(mini->fd[1]);
	mini->infile = mini->fd[0];
}

int	swap_fds(t_mini *mini, t_token *token)
{
	if (token->input_redir)
	{
		if (dup2(mini->infile, STDIN_FILENO) == -1)
			return (perror("dup2 error"), exit(EXIT_FAILURE), 1);
	}
	else if (mini->infile != STDIN_FILENO)
		if (dup2(mini->infile, STDIN_FILENO) == -1)
			return (perror("dup2 error"), exit(EXIT_FAILURE), 1);
	if (token->output_redir)
	{
		if (dup2(mini->outfile, STDOUT_FILENO) == -1)
			return (perror("dup2 error"), exit(EXIT_FAILURE), 1);
	}
	else if (!mini->is_last_cmd)
		if (dup2(mini->fd[1], STDOUT_FILENO) == -1)
			return (perror("dup2 error"), exit(EXIT_FAILURE), 1);
	close(mini->fd[0]);
	close(mini->fd[1]);
	if (token->is_builtin)
	{
		builtin_commands(mini, token);
		exit(EXIT_SUCCESS);
	}
	else if (execve(token->path, token->cmd, mini->env) == -1)
	{
		perror("Failed to execute command");
		exit(EXIT_FAILURE);
	}
	return (0);
}
