/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctommasi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 16:29:04 by ctommasi          #+#    #+#             */
/*   Updated: 2024/12/03 16:29:05 by ctommasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtins(char *cmd)
{
	return (!ft_strcmp(cmd, "history")
		|| !ft_strcmp(cmd, "env")
		|| !ft_strcmp(cmd, "echo")
		|| !ft_strcmp(cmd, "cd")
		|| !ft_strcmp(cmd, "pwd")
		|| !ft_strcmp(cmd, "export")
		|| !ft_strcmp(cmd, "unset")
		|| !ft_strcmp(cmd, "exit")
		|| !ft_strncmp(cmd, "$", 1));
}

int	is_output_redirect(char *cmd)
{
	return (!ft_strcmp(cmd, ">>") || !ft_strcmp(cmd, ">"));
}

int	is_input_redirect(char *cmd)
{
	return (!ft_strcmp(cmd, "<<") || !ft_strcmp(cmd, "<"));
}

int	is_redirect(char *cmd)
{
	return (is_input_redirect(cmd) || is_output_redirect(cmd));
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