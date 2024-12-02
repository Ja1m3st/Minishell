/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 16:02:40 by jaimesan          #+#    #+#             */
/*   Updated: 2024/12/02 15:07:40 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_command(char *cmd, char **envp)
{
	char	**args;
	char	*cmd_path;

	args = ft_split(cmd, ' ');
	if (!args)
		return (perror("Error\n"), exit(EXIT_FAILURE));
	cmd_path = ft_strjoin("/usr/bin/", args[0]);
	if (!cmd_path)
		return (exit(EXIT_FAILURE));
	execve(&cmd_path[0], args, envp);
	perror("Error: execve falló");
	free_arr(args);
	free(cmd_path);
	exit(EXIT_FAILURE);
}

int	ft_redirects(int in_fd, int mini_fd[], int i, t_mini *mini)
{
	if (dup2(in_fd, STDIN_FILENO) == -1)
		exit(EXIT_FAILURE);
	if (i < mini->total_args - 1)
	{
		if (dup2(mini_fd[1], STDOUT_FILENO) == -1)
			exit(EXIT_FAILURE);
	}
	else
	{
		if (dup2(mini->outfile, STDOUT_FILENO) == -1)
			exit(EXIT_FAILURE);
	}
	close(mini_fd[0]);
	close(mini_fd[1]);
	close(in_fd);
	execute_command(mini->split_full_cmds[i], mini->env);
	return (1);
}

void	pipex(t_mini *mini)
{
	int fd[2];
	int i;
	int in_fd;

	i = 0;
	in_fd = mini->infile;
	while (i < mini->total_args)
	{
		pipe(fd);
		mini->pid = fork();
		if (mini->pid == -1)
			return ;
		if (mini->pid == 0)
		{
			ft_redirects(in_fd, fd, i, mini);
			exit(EXIT_FAILURE);
		}
		close(fd[1]);
		if (in_fd != mini->infile)
			close(in_fd);
		in_fd = fd[0];
		i++;
		free_arr(mini->cmds);
	}
	while (i-- > 0)
		waitpid(mini->pid, NULL, 0);
}