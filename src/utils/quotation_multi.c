/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotation_multi.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 13:10:37 by jaimesan          #+#    #+#             */
/*   Updated: 2025/01/09 14:37:32 by jaimesan         ###   ########.fr       */
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
		|| str[*i + 1] == 'r' || str[*i + 1] == 'r' || str[*i + 1] == '\'')
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

int	process_input_multi(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\"' || str[i] == '`' || str[i] == '\'')
		{
				i++;
				continue ;
		}
		if (is_special_sequence(str[i], str[i + 1]))
		{
			if (handle_special_sequence(str, &i, &j) == 0)
				return (0);
		}
		else
			str[j++] = str[i];
		i++;
	}
	str[j] = '\0';
	return (1);
}
