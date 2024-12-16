/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 11:38:02 by jaimesan          #+#    #+#             */
/*   Updated: 2024/12/16 16:39:54 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_special_sequence(char current, char next)
{
	return (current == '\\' && (next == '\"' || next == '\''
			|| next == '\\' || next == 'n' || next == 't' || next == '\0'));
}

int	handle_special_sequence(char *str, int *i, int *j)
{
	if (str[*i + 1] == 'n' || str[*i + 1] == 't' || str[*i + 1] == 'a'
			|| str[*i + 1] == 'b' || str[*i + 1] == 'v' || str[*i + 1] == 'f' 
			|| str[*i + 1] == 'r')
	{
		str[(*j)++] = '\\';
		str[(*j)++] = str[++(*i)];
	}
	else if (str[*i + 1] == '\0')
		return (0);
	else
		str[(*j)++] = str[++(*i)];
	return (1);
}

int	process_input_multi(char *str, char chr)
{
	int	i;
	int	j;
	int	has_delimiters;
	int	count;

	has_delimiters = 0;
	i = 0;
	j = 0;
	count = 0;
	if (str[i] == chr)
	{
		count++;
		i++;
		has_delimiters = 1;
	}
	while (str[i] != '\0')
	{
		if (str[i] == '\"' && str[i - 1] != '\\')
			count++;
		if (is_special_sequence(str[i], str[i + 1]))
		{
			if (handle_special_sequence(str, &i, &j) == 0)
				return (0);
		}
		else if (has_delimiters == 0 && str[i] == '\\')
			str[j++] = str[++i];
		else
			str[j++] = str[i];
		i++;
	}
	if (str[i - 1] == chr && has_delimiters == 1)
		j--;
	str[j] = '\0';
	if (has_delimiters == 1 && (count % 2 != 0 || count == 1 ))
		return (0);
	return (1);
}

int	process_input_single(char *str, char chr)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (str[i] == chr)
	{
		i++;
		while (str[i] != '\0')
		{
			if (str[i] == '\\' && (str[i + 1] == '\"'
					|| str[i + 1] == '\'' || str[i + 1] == '\\'))
			{
				str[j++] = '\\';
				str[j++] = str[++i];
			}
			else if (str[i] == '\\' && str[i + 1] == 'n')
			{
				str[j++] = '\\';
				str[j++] = 'n';
				i++;
			}
			else
			{
				str[j++] = str[i];
			}
			i++;
		}
		if (i > 0 && str[i - 1] == chr)
			j--;
		str[j] = '\0';
		return (1);
	}
	return (0);
}

int	check_input_multi(char *str)
{
	int	i;
	int	count_back;
	int	cunt_quo;

	i = 0;
	cunt_quo = 0;
	count_back = 0;
	while (str[i] != 0)
	{
		if (str[i] == '\\')
		{
			if (str[i + 1] == 0)
				return (0);
			count_back++;
		}
		i++;
	}
	if (count_back == 0 || count_back == 1)
		return (1);
	if (count_back % 2 != 0)
		return (0);
	return (1);
}

int check_quotation(t_mini *mini, int i)
{
	while (mini->mini_cmds[i] && !ft_strchr(mini->mini_cmds[i], '~'))
	{
		if (mini->mini_cmds[i] && mini->mini_cmds[i][0] != '\'')
		{
			if (process_input_multi(mini->mini_cmds[i++], '"') == 0)
			{
				ft_printf("Error dquote\n");
				return (0);
			}
		}
		else
			process_input_single(mini->mini_cmds[i++], '\'');
	}
	return (1);
}