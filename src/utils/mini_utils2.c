/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctommasi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:40:19 by ctommasi          #+#    #+#             */
/*   Updated: 2024/12/12 16:40:20 by ctommasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"


// void process_command(t_mini *mini)
// {
// 	int	i;
// 	int	j;
// 	int	len;
// 	char	*current_cmd;
// 	int	current_cmd_len;
// 	t_quote_type current_quote;
	
// 	len = ft_strlen(mini->input);
// 	mini->quote_types = malloc(sizeof(char *) * len + 1);
// 	mini->mini_cmds = malloc(sizeof(char *) * len + 1);
// 	current_cmd_len = 0;
// 	current_quote = NO_QUOTE;
// 	current_cmd = malloc(len + 1);
// 	i = 0;
// 	j = 0;
// 	while (i < len)
// 	{
// 		char ch = mini->input[i];
// 		if (ch == '\'' && (current_quote == NO_QUOTE || current_quote == SINGLE_QUOTE))
// 		{
// 		    current_quote = (current_quote == SINGLE_QUOTE) ? NO_QUOTE : SINGLE_QUOTE;
// 		}
// 		else if (ch == '\"' && (current_quote == NO_QUOTE || current_quote == DOUBLE_QUOTE))
// 		{
// 		    current_quote = (current_quote == DOUBLE_QUOTE) ? NO_QUOTE : DOUBLE_QUOTE;
// 		}
// 		if (current_quote != NO_QUOTE || ch != ' ')
// 		{
// 		    current_cmd[current_cmd_len++] = ch;
// 		}
// 		if (ch == ' ' && current_quote == NO_QUOTE && current_cmd_len > 0)
// 		{
// 		    current_cmd[current_cmd_len] = '\0';
// 		    mini->mini_cmds[j++] = ft_strdup(current_cmd);
// 		    current_cmd_len = 0;
// 		}
// 		i++;
// 	}
// 	if (current_cmd_len > 0)
// 	{
// 		current_cmd[current_cmd_len] = '\0';
// 		mini->mini_cmds[j++] = ft_strdup(current_cmd);
// 	}
// 	mini->mini_cmds[j] = NULL;
// 	free(current_cmd);
// 	free(mini->quote_types);
// }

// void	ft_ptrdelchar(char *str, const char *chars)
// {
// 	int		i;
// 	int		j;

// 	if (!str || !chars)
// 		return ;
// 	i = 0;
// 	j = 0;
// 	while (str[i])
// 	{
// 		if (!ft_strchr(chars, str[i]))
// 			str[j++] = str[i];
// 		i++;
// 	}
// 	str[j] = '\0';
// }
