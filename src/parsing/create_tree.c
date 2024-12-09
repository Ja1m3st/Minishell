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
		return (token);
	token->cmd = NULL;
	token->path = NULL;
	token->type = NULL;
	token->file = NULL;
	token->delimeter = NULL;
	token->is_builtin = 0;
	token->is_last_cmd = 0;
	token->complete = 0;
	token->newline = 0;
	token->right = NULL;
	return (token);
}

void	ft_tokenadd_back(t_token **lst, t_token *token)
{
	t_token	*last;

	if (!lst || !token)
		return ;
	if (!*lst)
	{
		*lst = token;
		return ;
	}
	last = *lst;
	while (last->right)
		last = last->right;
	last->right = token;
}
