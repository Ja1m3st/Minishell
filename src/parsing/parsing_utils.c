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

int is_redirect(char *cmd)
{
	return (is_input_redirect(cmd) || is_output_redirect(cmd));
}

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
	return (token);
}

void	ft_tokenadd_back(t_token **lst, t_token *token)
{
	t_token	*last;
	t_token *temp;

	
    if (!lst || !token)
        return;

    if (!*lst)
    {
        *lst = token;
        return;
    }
	last = *lst;
	while (last->next)
		last = last->next;
	last->next = token;
	if (token->do_swap)
    {
        temp = last->next;
        last->next = token->next;
        token->next = temp;
    }
}

void print_tokens(t_mini *mini)
{
    t_token *current = *(t_token **)mini->list;
    int		i = 0;

    while (current)
    {
        printf("Token %d.- :\n", i);
        if (current->cmd)
        {
            for (int i = 0; current->cmd[i]; i++)
                printf("  cmd[%d]: %s\n", i, current->cmd[i]);
        }
		printf("  do_swap???: %d\n", current->do_swap);
        printf("  is_builtin: %d\n", current->is_builtin);
		printf("  path: %s\n", current->path);
        printf("  type: %s\n", current->type);
        printf("  file: %s\n", current->file);
        printf("----------------------\n");
        current = current->next;
	i++;
    }
}