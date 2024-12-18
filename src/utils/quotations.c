/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 11:38:02 by jaimesan          #+#    #+#             */
/*   Updated: 2024/12/18 13:12:53 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_quo(char *str)
{
	int	i;
	int	in_single_quote;
	int	in_double_quote;

	i = 0;
	in_single_quote = 0;
	in_double_quote = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\"' && in_single_quote == 0)
			in_double_quote = !in_double_quote;
		else if (str[i] == '\'' && in_double_quote == 0)
			in_single_quote = !in_single_quote;
		else if (str[i] == '\\' && in_single_quote == 0 && str[i + 1] != '\0')
			i++;
		i++;
	}
	if (in_single_quote || in_double_quote)
		return (0);
	return (1);
}

int	check_quotation(t_mini *mini)
{
	int	i;

	i = 0;
	while (mini->mini_cmds[i] != 0 && !ft_strchr(mini->mini_cmds[i], '~'))
	{
		if (check_quo(mini->mini_cmds[i]) == 0)
			return (free_main(mini), perror("Unclosed quotes\n"), 0);
		if (mini->mini_cmds[i][0] == '\"')
		{
			if (process_input_multi(mini->mini_cmds[i]) == 0)
				return (free_main(mini), perror("Error dquote\n"), 0);
		}
		else if (mini->mini_cmds[i][0] == '\'')
		{
			if (process_input_single(mini->mini_cmds[i]) == 0)
				return (free_main(mini), perror("Error dquote\n"), 0);
		}
		else
		{
			if (process_input_none(mini->mini_cmds[i]) == 0)
				return (free_main(mini), perror("Invalid backslash\n"), 0);
		}
		i++;
	}
	return (1);
}
