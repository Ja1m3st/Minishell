/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 11:38:02 by jaimesan          #+#    #+#             */
/*   Updated: 2024/12/16 12:32:07 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_special_sequence(char current, char next)
{
	return (current == '\\' && (next == '\"' || next == '\''
			|| next == '\\' || next == 'n' || next == 't'));
}

void	handle_special_sequence(char *str, int *i, int *j)
{
	if (str[*i + 1] == 'n' || str[*i + 1] == 't')
	{
		str[(*j)++] = '\\';
		str[(*j)++] = str[++(*i)];
	}
	else
		str[(*j)++] = str[++(*i)];
}

int	process_input_multi(char *str, char chr)
{
	int	i;
	int	j;
	int	has_delimiters;

	has_delimiters = 0;
	i = 0;
	j = 0;
	if (str[i] == chr)
	{
		i++;
		has_delimiters = 1;
	}
	while (str[i] != '\0')
	{
		if (is_special_sequence(str[i], str[i + 1]))
			handle_special_sequence(str, &i, &j);
		else
			str[j++] = str[i];
		i++;
	}
	if (str[i - 1] == chr && has_delimiters == 1)
		j--;
	str[j] = '\0';
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
	int	count;

	i = 0;
	count = 0;
/* 	while (str[i] != 0)
	{
		if (str[i] == '\"' && str[])
			count++;
		i++;
	}
	if (count % 2 != 0) */
	return (1);
}