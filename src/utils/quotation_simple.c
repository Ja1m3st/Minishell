/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotation_simple.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 13:10:06 by jaimesan          #+#    #+#             */
/*   Updated: 2024/12/17 13:14:06 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			str[j++] = str[i];
			i++;
		}
		if (str[i - 1] == chr)
			j--;
		str[j] = '\0';
	}
	return (1);
}
