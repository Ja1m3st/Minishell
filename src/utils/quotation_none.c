/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotation_none.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 13:12:17 by jaimesan          #+#    #+#             */
/*   Updated: 2024/12/17 13:16:40 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_special_sequence_none(char current, char next)
{
	return (current == '\\' && (next == '\"' || next == '\''
			|| next == '\\' || next == 'n' || next == 't' || next == '\0'));
}

int	handle_special_sequence_none(char *str, int *i, int *j)
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

int	process_input_none(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (is_special_sequence_none(str[i], str[i + 1]))
		{
			if (handle_special_sequence_none(str, &i, &j) == 0)
				return (0);
		}
		else if (str[i] == '\\')
			str[j++] = str[++i];
		else
			str[j++] = str[i];
		i++;
	}
	str[j] = '\0';
	return (1);
}
