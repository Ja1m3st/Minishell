/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 13:30:27 by jaimesan          #+#    #+#             */
/*   Updated: 2024/12/13 13:41:57 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_terminal_commands(t_mini *mini, t_token *token)
{
	if (token->path)
		free(token->path);
	token->path= ft_strjoin("/usr/bin/", token->cmd[0]);
	if (!token->path)
		return ;
	mini->pid = fork();
	if (mini->pid == -1)
		return ;
	if (mini->pid == 0)
	{
		if (execve(token->cmd[0], token->cmd, mini->env) == -1)
		{
			execve(token->path, token->cmd, mini->env);
			perror("Error: execve falló");
		}
		return ;
	}
	waitpid(mini->pid, NULL, 0);
}

void	execute_commands(t_mini *mini)
{
	t_token	*token;

	if (!mini->commands)
		return ;
	token = *mini->commands;
	if (!token->next)
	{
		if (token->input_file || token->input_redir
			|| token->output_file || token->output_redir)
			set_in_out_file(mini, token);
		if (token->is_builtin)
		{
			builtin_commands(mini, token);
			return ;
		}
		else
		{
			get_terminal_commands(mini, token);
			return ;
		}
	}
	mini->temp_fd = mini->infile;
	while (token)
	{
		if (!token->next)
			mini->is_last_cmd = 1;
		set_in_out_file(mini, token);
		pipex(mini, token);
		token = token->next;
	}
	init_fds(mini);
	mini->is_last_cmd = 0;
	waitpid(mini->pid, NULL, 0);
}

void	set_in_out_file(t_mini *mini, t_token *token)
{
	if (token->input_redir && !ft_strcmp(token->input_redir, "<"))
	{
		input_redirection(mini, token);
	}
	else if (token->input_redir && !ft_strcmp(token->input_redir, "<<"))
	{
		here_doc(mini, token);
	}
	if (token->output_redir && !ft_strcmp(token->output_redir, ">"))
	{
		mini->outfile = open(token->output_file,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (mini->outfile == -1)
			return (perror("Error opening outfile.\n"));
	}
	else if (token->output_redir && !ft_strcmp(token->output_redir, ">>"))
	{
		mini->outfile = open(token->output_file,
				O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (mini->outfile == -1)
			return (perror("Error opening outfile.\n"));
	}
}
