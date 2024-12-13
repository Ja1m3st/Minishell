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

void	execute_commands(t_mini *mini)
{
	t_token	*token;

	if (!mini->commands)
		return ;
	token = *mini->commands;
	if (!token->next)
	{
		get_terminal_commands(mini, token);
		return ;
	}
	init_fds(mini);
	mini->temp_fd = STDIN_FILENO;
	while (token)
	{
		if (!token->next)
			mini->is_last_cmd = 1;
		set_in_out_file(mini, token);
		pipex(mini, token);
		restore_fds(mini);
		token = token->next;
	}
	mini->is_last_cmd = 0;
	waitpid(mini->pid, NULL, 0);
	close(mini->og_infile);
	close(mini->og_outfile);
}

void	set_in_out_file(t_mini *mini, t_token *token)
{
	if (token->input_redir && !ft_strcmp(token->input_redir, "<"))
	{
		mini->infile = open(token->input_file, O_RDONLY);
		if (mini->infile == -1)
			return (perror("Error opening file.\n"));
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
			return (perror("Error redirecting to file.\n"));
	}
	else if (token->output_redir && !ft_strcmp(token->output_redir, ">>"))
	{
		mini->outfile = open(token->output_file,
				O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (mini->outfile == -1)
			return (perror("Error appending to file.\n"));
	}
}

void	get_terminal_commands(t_mini *mini, t_token *token)
{
	if (!token || !mini)
		return ;
	if (token->input_redir || token->output_redir)
		set_in_out_file(mini, token);
	if (token->is_builtin)
		return (builtin_commands(mini, token));
	mini->pid = fork();
	if (mini->pid == -1)
		return ;
	if (mini->pid == 0)
	{
		if (dup2(mini->outfile, STDOUT_FILENO) == -1)
			return (perror("Dup2 outfile error.\n"));
		if (dup2(mini->infile, STDIN_FILENO) == -1)
			return (perror("Dup2 infile error\n"));
		if (execve(token->path, token->cmd, mini->env) == -1)
			return (perror("Execve fail.\n"));
	}
	waitpid(mini->pid, NULL, 0);
}
