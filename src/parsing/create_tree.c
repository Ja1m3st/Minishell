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
	token->do_swap = 0;
	token->complete = 0;
	token->right = NULL;
	token->left = NULL;
	return (token);
}

void	ft_tokenadd_right(t_token **lst, t_token *token)
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

void	ft_tokenadd_left(t_token **lst, t_token *token)
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
	if (last->right)
	{
		while (last->right)
			last = last->right;
	}
	while (last->left)
		last = last->left;
	last->left = token;
} 
