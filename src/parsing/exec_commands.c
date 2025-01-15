/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 13:30:27 by jaimesan          #+#    #+#             */
/*   Updated: 2025/01/15 13:52:47 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_commands(t_mini *mini)
{
	t_token	*token;

	if (!mini->commands)
		return ;
	init_fds(mini);
	token = *mini->commands;
	if (token && !token->next && token->is_builtin)
		return (set_in_out_file(mini, token), builtin_commands(mini, token));
	if (pipe(mini->fd) == -1)
		return (perror("Pipe error\n"));
	while (token)
	{
		if (!token->next)
			mini->is_last_cmd = 1;
		pipex(mini, token);
		signal(SIGINT, &handle_sigint);
		mini->is_first_cmd = 0;
		token = token->next;
	}
	restore_fds(mini);
}

void	set_in_out_file(t_mini *mini, t_token *token)
{
	if (token->input_redir && !ft_strcmp(token->input_redir, "<"))
	{
		mini->infile = open(token->input_file, O_RDONLY);
		if (mini->infile == -1)
		{
			perror("Error opening file.\n");
			g_status = 2;
			exit(g_status);
		}
	}
	else if (token->input_redir && !ft_strcmp(token->input_redir, "<<"))
	{
		here_doc(mini, token);
	}
	set_in_out_file2(mini, token);
}

void	set_in_out_file2(t_mini *mini, t_token *token)
{
	if (token->output_redir && !ft_strcmp(token->output_redir, ">"))
	{
		mini->outfile = open(token->output_file,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (mini->outfile == -1)
		{
			perror("Error redirecting to file.\n");
			g_status = 2;
			exit(g_status);
		}
	}
	else if (token->output_redir && !ft_strcmp(token->output_redir, ">>"))
	{
		mini->outfile = open(token->output_file,
				O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (mini->outfile == -1)
		{
			perror("Error appending to file.\n");
			g_status = 2;
			exit(g_status);
		}
	}
}
