/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctommasi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 16:17:18 by ctommasi          #+#    #+#             */
/*   Updated: 2024/12/05 16:17:19 by ctommasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ft_newtoken(t_token *token)
{
	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->cmd = NULL;
	token->path = NULL;
	token->input_redir = NULL;
	token->output_redir = NULL;
	token->input_file = NULL;
	token->output_file = NULL;
	token->delimeter = NULL;
	token->pipe = NULL;
	token->is_builtin = 0;
	token->complete = 0;
	token->newline = 0;
	token->next = NULL;
	return (token);
}

void	ft_tokenadd_back(t_mini *mini, t_token *token)
{
	t_token	*last;

	if (!mini->commands || !token)
		return ;
	if (!*mini->commands)
	{
		*mini->commands = token;
		return ;
	}
	last = *mini->commands;
	while (last->next)
		last = last->next;
	last->next = token;
}
