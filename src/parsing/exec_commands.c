/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 13:30:27 by jaimesan          #+#    #+#             */
/*   Updated: 2024/12/02 16:10:26 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_cmds(t_mini *mini)
{
	t_token *token;

	if (!mini->commands)
		return (perror("mini->commands is NULL\n"));
	token = *mini->commands;
	while (token)
	{
		if (!token->next)
			mini->is_last_cmd = 1;
		if (!ft_strcmp(token->input_redir, "<"))
		{
			mini->infile = open(token->input_file, O_RDONLY);
			if (mini->infile == -1)
				return (perror("Error opening infile.\n"));
		}
		else if (!ft_strcmp(token->input_redir, "<<"))
		{
			mini->infile = 0;
			if (mini->infile == -1)
				return (perror("Error opening outfile.\n"));
		}
		if (!ft_strcmp(token->output_redir, ">"))
		{
			mini->outfile = open(token->output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (mini->outfile == -1)
				return (perror("Error opening outfile.\n"));
		}
		else if (!ft_strcmp(token->output_redir, ">>"))
		{
			mini->outfile = open(token->output_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (mini->outfile == -1)
				return (perror("Error opening outfile.\n"));
		}
		pipex(mini, token);
		token = token->next;
	}
	waitpid(mini->pid, NULL, 0);
	mini->is_last_cmd = 1;
}

void	pipex(t_mini *mini, t_token *token)
{
	mini->temp_fd = mini->infile;
	if (pipe(mini->fd) == -1)
		return (perror("pipe error\n"));
	mini->pid = fork();
	if (mini->pid == -1)
		return (perror("fork error\n"));
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
		builtin_cmds(mini, token);
	else
	{
		if (execve(token->path, token->cmd, mini->env) == -1)
			return (perror("executing command\n"), exit(EXIT_FAILURE), 1);
	}
	return (0);
}

void	builtin_cmds(t_mini *mini, t_token *token)
{
	if (!ft_strcmp(token->cmd[0], "history"))
		print_history();
	else if (!ft_strcmp(token->cmd[0], "env"))
		print_env(mini);
	else if (!ft_strcmp(token->cmd[0], "echo"))
		echo(token);
	else if (!ft_strcmp(token->cmd[0], "pwd"))
		print_pwd(mini);
	else if (!ft_strcmp(token->cmd[0], "cd"))
		cd(mini);
	else if (!ft_strcmp(token->cmd[0], "export"))
		export(mini);
	else if (!ft_strcmp(token->cmd[0], "unset"))
		unset(mini);
	else if (!ft_strncmp(token->cmd[0], "$", 1))
		printf("%s\n", get_var(mini));
	else if (!ft_strcmp(token->cmd[0], "exit"))
		error(mini, '!');
}