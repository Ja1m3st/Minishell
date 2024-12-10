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
		if (token->input_redir || token->output_redir)
			set_in_out_file(mini, token);
		pipex(mini, token);
		token = token->next;
	}
	waitpid(mini->pid, NULL, 0);
	mini->is_last_cmd = 0;
}

void	set_in_out_file(t_mini *mini, t_token *token)
{
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
}
