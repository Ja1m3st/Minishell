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

int	count_no_quote_chars(t_mini *mini, t_quote_type *quote, int *i)
{
	int	count;
	int	is_word;

	count = 0;
	is_word = 0;
	while (mini->input[*i] && mini->input[*i] != ' ' && *quote == NO_QUOTE
		&& !is_delimeter(mini->input[*i])
		&& ((mini->input[*i] != '>' && mini->input[(*i) + 1] != '>')
			&& (mini->input[*i] != '<' && mini->input[(*i) + 1] != '<')))
	{
		*quote = get_quote(*quote, mini->input[*i]);
		is_word = 1;
		(*i)++;
	}
	if (is_word)
		count++;
	return (count);
}

int	count_no_quote_single_redir(t_mini *mini, t_quote_type quote, int *i)
{
	if (mini->input[*i] && quote == NO_QUOTE)
	{
		if ((mini->input[*i] == '>' || mini->input[(*i)] == '<')
			&& (mini->input[*i + 1] != mini->input[*i]))
		{
			(*i)++;
			return (1);
		}
		if ((mini->input[*i] == '>' && mini->input[*i + 1] == '>')
			|| (mini->input[*i] == '<' && mini->input[*i + 1] == '<'))
		{
			(*i)++;
			return (1);
		}
	}
	return (0);
}

int	count_quote_chars(t_mini *mini, t_quote_type *quote, int *i)
{
	int	count;

	count = 0;
	if (*quote != NO_QUOTE)
	{
		count = 1;
		(*i)++;
		while (mini->input[*i] && *quote == NO_QUOTE)
		{
			*quote = get_quote(*quote, mini->input[*i]);
			(*i)++;
		}
		*quote = NO_QUOTE;
	}
	return (count);
}

int	count_commands(t_mini *mini)
{
	int				i;
	int				count;
	t_quote_type	quote;

	i = 0;
	count = 0;
	quote = NO_QUOTE;
	while (mini->input[i])
	{
		quote = get_quote(quote, mini->input[i]);
		count += count_no_quote_chars(mini, &quote, &i);
		count += count_no_quote_single_redir(mini, quote, &i);
		count += count_quote_chars(mini, &quote, &i);
		i++;
	}
	return (count);
}
