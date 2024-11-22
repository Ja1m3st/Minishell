/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_save_static.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctommasi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 12:31:40 by ctommasi          #+#    #+#             */
/*   Updated: 2024/11/01 12:31:41 by ctommasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_save_static(char *total_chars)
{
	char	*new_chars;
	size_t	i;
	size_t	j;

	i = 0;
	while (total_chars[i] && total_chars[i] != '\n')
		i++;
	if (total_chars[i] == '\0')
		return (free(total_chars), NULL);
	new_chars = ft_calloc_z(ft_strlen(total_chars) - i + 1, sizeof(char));
	if (new_chars == NULL)
		return (free(total_chars), NULL);
	i++;
	j = 0;
	while (total_chars[i])
		new_chars[j++] = total_chars[i++];
	free(total_chars);
	return (new_chars);
}
