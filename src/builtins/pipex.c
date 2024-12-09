/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 16:02:40 by jaimesan          #+#    #+#             */
/*   Updated: 2024/12/09 14:06:58 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipex(t_mini *mini)
{
	int	fd[2];
	int	i;
	int	in_fd;

	i = 0;
	in_fd = mini->infile;
	while (i < mini->total_args)
	{
		mini->cmds = ft_split(mini->split_full_cmds[i], ' ');
		pipe(fd);
		mini->pid = fork();
		if (mini->pid == -1)
			return ;
		if (mini->pid == 0)
			redirect(in_fd, fd, i, mini);
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

int	redirect(int in_fd, int mini_fd[], int i, t_mini *mini)
{
	if (dup2(in_fd, STDIN_FILENO) == -1)
		exit(EXIT_FAILURE);
	if (ft_strchr(mini->split_full_cmds[i], '>') || ft_strchr(mini->split_full_cmds[i], '<'))
	{
		t_redir *block = redir(mini, i);
/* 		print_redir_list(block); */
		proces(block, mini);
		exit(EXIT_SUCCESS);
	}
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
	if (is_builtin(mini->cmds[0]))
		execute_builtins(mini, 1);
	else
		execute_command(mini->split_full_cmds[i], mini->env);
	return (1);
}

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
