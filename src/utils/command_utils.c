/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctommasi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 12:36:16 by ctommasi          #+#    #+#             */
/*   Updated: 2024/12/11 12:36:18 by ctommasi         ###   ########.fr       */
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

int	count_commands(t_mini *mini)
{
	int				i;
	int				count;
	int				is_in_word;
	t_quote_type	quote;

	i = 0;
	count = 0;
	is_in_word = 0;
	quote = NO_QUOTE;
	while (mini->input[i])
	{
		quote = get_quote(quote, mini->input[i]);
		if (quote != NO_QUOTE || mini->input[i] != ' ')
		{
			if (!is_in_word)
			{
				count++;
				is_in_word = 1;
			}
		}
		else if (mini->input[i] == ' ' && quote == NO_QUOTE)
			is_in_word = 0;
		i++;
	}
	return (count);
}
