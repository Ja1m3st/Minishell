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

int	is_redirect(char *cmd)
{
	return (!ft_strcmp(cmd, ">>")
		|| !ft_strcmp(cmd, ">")
		|| !ft_strcmp(cmd, "<<")
		|| !ft_strcmp(cmd, "<"));
}

t_token	*ft_newtoken(t_token *new)
{
	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		return (new);
	new->cmd = NULL;
	new->mods = NULL;
	new->is_builtin = 0;
	new->type = NULL;
	new->file = NULL;
	new->redir_count = 0;
	new->next = NULL;
	return (new);
}

void	ft_tokenadd_back(t_token **lst, t_token *new)
{
	t_token	*last;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = *lst;
	while (last->next)
		last = last->next;
	last->next = new;
}
