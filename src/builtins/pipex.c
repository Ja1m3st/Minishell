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
	int	fd[2];
	int	temp_fd;

	temp_fd = mini->infile;
	if (pipe(fd) == -1)
	{
		perror("pipe error\n");
		exit(EXIT_FAILURE);
	}
	printf("Pipe created: fd[0] = %d, fd[1] = %d\n", fd[0], fd[1]);
	mini->pid = fork();
	if (mini->pid == -1)
	{
		perror("fork error\n");
		return ;
	}
	if (mini->pid == 0)
		swap_fds(mini, token, temp_fd, fd);
	close(fd[1]);
	if (temp_fd != mini->infile)
		close(temp_fd);
	temp_fd = fd[0];
	waitpid(mini->pid, NULL, 0);
}

int	swap_fds(t_mini *mini, t_token *token, int temp_fd, int fd[])
{
	if (dup2(temp_fd, STDIN_FILENO) == -1)
	{
		perror("dup2 temp_fd\n");
		exit(EXIT_FAILURE);
	}	
	if (token->is_last_cmd)
	{
		if (dup2(fd[1], STDOUT_FILENO) == -1)
		{
			perror("dup2 fd[1]\n");
			exit(EXIT_FAILURE);
		}
			
	}
	else
	{
		if (dup2(mini->outfile, STDOUT_FILENO) == -1)
		{
			perror("dup2 outfile\n");
			exit(EXIT_FAILURE);
		}
			
	}
	close(fd[0]);
	close(fd[1]);
	close(temp_fd);
	if (token->is_builtin)
		builtin_cmds(mini, token);
	else
	{
		if (execve(token->path, token->cmd, mini->env) == -1)
			perror("executing command\n");
			exit(EXIT_FAILURE);
	}
	return (1);
}

