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

int remove_quotes(char *str)
{
	int len = strlen(str);
	if ((str[0] == '"' && str[len - 1] == '"') || (str[0] == '\'' && str[len - 1] == '\''))
	{
		memmove(str, str + 1, len - 2);
		str[len - 2] = '\0';
		return 1;
	}
	return 0;
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
	if (remove_quotes(str))
		printf("Removed quotes: %s\n", str);

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
	t_token	*current_token;
	int	i;

	current_token = *(mini->commands);
	while (current_token)
	{
		i = 0;
		while (current_token->cmd[i] != NULL)
		{
			call_remove_quotes(mini, current_token->cmd[i]);
			i++;
		}
		if (!is_builtin(current_token->cmd[0]))
			call_remove_quotes(mini, current_token->path);
		if (current_token->input_file)
			call_remove_quotes(mini, current_token->input_file);
		if (current_token->output_file)
			call_remove_quotes(mini, current_token->output_file);
		current_token = current_token->next;
	}
	return (1);
}
