/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctommasi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 10:27:59 by ctommasi          #+#    #+#             */
/*   Updated: 2024/12/03 10:28:00 by ctommasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_commands(t_mini *mini, char **cmds)
{
	t_token *new_token;
	char	*temp;

	if (!cmds || !*cmds)
		return ;
	new_token = ft_newtoken(NULL);
	while (*cmds)
	{
		if (is_redirect(*cmds))
		{
			new_token->type = ft_strdup(*cmds);
			cmds++;
			if (*cmds)
				new_token->file = ft_strdup(*cmds);
			else
				perror("No file found.\n");
		}
		else if (is_builtins(*cmds))
		{
			new_token->is_builtin = 1;
			temp = ft_strdup(*cmds);
			cmds++;
			if (*cmds && !is_redirect(*cmds) && ft_strcmp(*cmds, "|"))
				new_token->mods = ft_strdup(*cmds);
			new_token->cmd = ft_split(ft_strjoin(ft_strjoin(temp, " "), new_token->mods), ' ');
			free(temp);
		}
		else if (!ft_strcmp(*cmds, "|"))
		{
			new_token->type = ft_strdup(*cmds);
			cmds++;
			break ;
		}
		else
		{
			temp = ft_strdup(*cmds);
			cmds++;
			if (*cmds && !is_redirect(*cmds) && ft_strcmp(*cmds, "|"))
				new_token->mods = ft_strdup(*cmds);
			new_token->cmd = ft_split(ft_strjoin(ft_strjoin(temp, " "), new_token->mods), ' ');
			free(temp);
		}
		cmds++;
	}
	ft_tokenadd_back((t_token **)mini->list, new_token);
	if (*cmds)
		init_commands(mini, cmds);
	return (print_tokens(mini));
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
        printf("  is_builtin: %d\n", current->is_builtin);
        printf("  type: %s\n", current->type);
        printf("  file: %s\n", current->file);
        printf("----------------------\n");
        current = current->next;
	i++;
    }
}


