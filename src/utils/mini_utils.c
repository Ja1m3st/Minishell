/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 13:22:34 by jaimesan          #+#    #+#             */
/*   Updated: 2024/11/25 13:24:56 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void free_char_array(char **array)
{
    int i;

    i = 0;
    if (!array)
        return ;
    while (array[i])
	{
        free(array[i]);
        array[i] = NULL;
        i++;
    }
    free(array);
    array = NULL;
}

int	array_len(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}