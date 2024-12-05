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
	token->mods = NULL;
	token->is_builtin = 0;
	token->do_swap = 0;
	token->type = NULL;
	token->file = NULL;
	token->redir_count = 0;
	token->next = NULL;
	token->path = NULL;
	token->complete = 0;
	token->delimeter = NULL;
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
	while (last->next)
		last = last->next;
	last->next = token;
	if (last->do_swap == 1)
		do_swap(lst, token);
}

void	do_swap(t_token **lst, t_token *token)
{
	t_token	*cur;
	t_token	*temp;
	char	*temp_type;
	char	*temp_delimeter;

	cur = *lst;
	while (cur->next)
		cur = cur->next;
	temp = cur->next;
	temp_type = temp->type;
	temp_delimeter = temp->delimeter;
	cur->next = token->next;
	cur->next->type = token->next->type;
	cur->next->delimeter = token->next->delimeter;
	token->next = temp;
	token->next->type = temp_type;
	token->next->delimeter = temp_delimeter;
}
