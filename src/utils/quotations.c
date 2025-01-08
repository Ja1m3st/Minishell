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

int check_quotation(t_mini *mini)
{
    t_token *current_token;
    int     i;

    current_token = *(mini->commands);
    while (current_token)
    {
        i = 0;
        while (current_token->cmd[i] != NULL)
        {
            if (!check_quo(current_token->cmd[i]))
                return (free_main(mini), perror("Unclosed quotes\n"), 0);

            if (remove_quotes(current_token->cmd[i]))
                printf("Removed quotes: %s\n", current_token->cmd[i]);

            if (current_token->cmd[i][0] == '"')
            {
                if (!process_input_multi(current_token->cmd[i]))
                    return (free_main(mini), perror("Error dquote\n"), 0);
            }
            else if (current_token->cmd[i][0] == '\'')
            {
                if (!process_input_single(current_token->cmd[i]))
                    return (free_main(mini), perror("Error squote\n"), 0);
            }
            else
            {
                if (!process_input_none(current_token->cmd[i]))
                    return (free_main(mini), perror("Invalid backslash\n"), 0);
            }
            i++;
        }
        current_token = current_token->next;
    }
    return 1;
}
