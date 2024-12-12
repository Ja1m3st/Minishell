/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctommasi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:40:19 by ctommasi          #+#    #+#             */
/*   Updated: 2024/12/12 16:40:20 by ctommasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_quote_type	get_quote(t_quote_type quote, char c)
{
	if (c == '\'')
	{
		if (quote == NO_QUOTE)
			return (SINGLE_QUOTE);
		else if (quote == SINGLE_QUOTE)
			return (NO_QUOTE);
	}
	else if (c == '\"')
	{
		if (quote == NO_QUOTE)
			return (DOUBLE_QUOTE);
		else if (quote == DOUBLE_QUOTE)
			return (NO_QUOTE);
	}
	return (quote);
}

void	process_commands(t_mini *mini)
{
	int		i;
	int		j;
	int		k;
	char	*cmd;
	t_quote_type	quote;
 
	i = 0;
	j = 0;
	k = 0;
	cmd = NULL;
	quote = NO_QUOTE;
	mini->mini_cmds = malloc(sizeof(char *));
	if (!mini->mini_cmds)
		return ;
	while (mini->input[i])
	{
		quote = get_quote(quote, mini->input[i]);
		if (quote != NO_QUOTE || mini->input[i] != ' ')
		{
			cmd = ft_realloc(cmd, k, k + 2);
			cmd[k++] = mini->input[i];
			cmd[k] = '\0';
		}
		if (quote == NO_QUOTE && mini->input[i] == ' ' && k > 0)
		{
			mini->mini_cmds = ft_realloc(mini->mini_cmds, j * sizeof(char *), (j + 2) * sizeof(char *));
			mini->mini_cmds[j++] = cmd;
			mini->mini_cmds[j] = NULL;
			k = 0;
		}
		i++;
	}
	if (k > 0)
	{
		mini->mini_cmds = ft_realloc(mini->mini_cmds, j * sizeof(char *), (j + 2) * sizeof(char *));
		mini->mini_cmds[j++] = cmd;
	}
	mini->mini_cmds = ft_realloc(mini->mini_cmds, j * sizeof(char *), (j + 2) * sizeof(char *));
	mini->mini_cmds[j] = NULL;
}

