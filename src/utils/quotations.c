/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 11:38:02 by jaimesan          #+#    #+#             */
/*   Updated: 2025/01/09 14:42:18 by jaimesan         ###   ########.fr       */
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
	if (str[0] == '"')
	{
		if (remove_quotes(str))
			printf("Removed quotes: %s\n", str);
		if (!process_input_multi(str))
			return (free_main(mini), perror("Error dquote\n"), 0);
	}
	else if (str[0] == '\'')
	{
		if (remove_quotes(str))
			printf("Removed quotes: %s\n", str);
		if (!process_input_single(str))
			return (free_main(mini), perror("Error squote\n"), 0);
	}
	else
	{
		remove_quotes(str);
		if (!process_input_none(str))
			return (free_main(mini), perror("Invalid backslash\n"), 0);
	}
	return (1);
}

int	check_quotation(t_mini *mini)
{
	t_token	*token;
	int		i;

	token = *(mini->commands);
	while (token)
	{
		i = 0;
		while (token->cmd[i] != NULL)
		{
			if (call_remove_quotes(mini, token->cmd[i]) == 0)
				return (0);
			if (ft_strchr(token->cmd[i], '$'))
				token->cmd[i] = expand_variable(mini, token->cmd[i]);
			if (is_builtin(token->cmd[i]))
				token->is_builtin = 1;
			i++;
		}
		token->path = ft_strjoin("/usr/bin/", token->cmd[0]);
		if (token->input_file)
			call_remove_quotes(mini, token->input_file);
		if (token->output_file)
			call_remove_quotes(mini, token->output_file);
		token = token->next;
	}
	return (1);
}
