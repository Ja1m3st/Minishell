/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 11:38:02 by jaimesan          #+#    #+#             */
/*   Updated: 2025/01/08 15:57:32 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	remove_quotes(char *str)
{
	int	len;

	len = strlen(str);
	if ((str[0] == '"' && str[len - 1] == '"')
		|| (str[0] == '\'' && str[len - 1] == '\''))
	{
		ft_memmove(str, str + 1, len - 2);
		str[len - 2] = '\0';
		return (1);
	}
	return (0);
}

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

int	call_remove_quotes(t_mini *mini, char *str)
{
	if (!check_quo(str))
		return (free_main(mini), perror("Unclosed quotes\n"), 0);
	remove_quotes(str);
	if (str[0] == '"')
	{
		if (!process_input_multi(str))
			return (free_main(mini), perror("Error dquote\n"), 0);
	}
	else if (str[0] == '\'')
	{
		if (!process_input_single(str))
			return (free_main(mini), perror("Error squote\n"), 0);
	}
	else
	{
		if (!process_input_none(str))
			return (free_main(mini), perror("Invalid backslash\n"), 0);
	}
	return (1);
}

int	check_quotation(t_mini *mini)
{
	t_token	*cur;
	int		i;

	cur = *(mini->commands);
	while (cur)
	{
		i = 0;
		while (cur->cmd[i] != NULL)
		{
			call_remove_quotes(mini, cur->cmd[i]);
			if (ft_strchr(cur->cmd[i], '$'))
				cur->cmd[i] = expand_variable(mini, cur->cmd[i]);
			i++;
		}
		if (!is_builtin(cur->cmd[0]))
			call_remove_quotes(mini, cur->path);
		if (cur->input_file)
			call_remove_quotes(mini, cur->input_file);
		if (cur->output_file)
			call_remove_quotes(mini, cur->output_file);
		cur = cur->next;
	}
	return (1);
}
