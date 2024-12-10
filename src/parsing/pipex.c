/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 16:02:40 by jaimesan          #+#    #+#             */
/*   Updated: 2024/12/02 16:09:50 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipex(t_mini *mini, t_token *token)
{
	if (token->cmd && token->cmd[0] && !ft_strcmp(token->cmd[0], "exit"))
		error(mini, '!');
	mini->temp_fd = mini->infile;
	if (pipe(mini->fd) == -1)
		return (perror("Pipe error\n"));
	mini->pid = fork();
	if (mini->pid == -1)
		return (perror("Fork error\n"));
	if (mini->pid == 0)
		swap_fds(mini, token);
	close(mini->fd[1]);
	if (mini->temp_fd != mini->infile)
		close(mini->temp_fd);
	mini->temp_fd = mini->fd[0];
}

int	swap_fds(t_mini *mini, t_token *token)
{
	if (dup2(mini->temp_fd, STDIN_FILENO) == -1)
		return (perror("dup2 temp_fd\n"), exit(EXIT_FAILURE), 1);
	if (!mini->is_last_cmd)
	{
		if (dup2(mini->fd[1], STDOUT_FILENO) == -1)
			return (perror("dup2 fd[1]\n"), exit(EXIT_FAILURE), 1);
	}
	else
	{
		if (dup2(mini->outfile, STDOUT_FILENO) == -1)
			return (perror("dup2 outfile\n"), exit(EXIT_FAILURE), 1);
	}
	close(mini->fd[0]);
	close(mini->fd[1]);
	close(mini->temp_fd);
	if (token->is_builtin)
	{
		builtin_cmds(mini, token);
		exit(EXIT_SUCCESS);
	}
	else
		if (execve(token->path, token->cmd, mini->env) == -1)
			return (perror("executing command\n"), exit(EXIT_FAILURE), 1);
	return (0);
}
