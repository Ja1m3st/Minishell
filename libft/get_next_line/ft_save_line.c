/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_save_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctommasi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 12:31:52 by ctommasi          #+#    #+#             */
/*   Updated: 2024/11/01 12:31:55 by ctommasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_save_line(char *total_chars)
{
	char	*line;
	size_t	i;

	i = 0;
	if (total_chars[i] == '\0')
		return (NULL);
	while (total_chars[i] && total_chars[i] != '\n')
		i++;
	line = ft_calloc_z(i + 2, sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (total_chars[i] && total_chars[i] != '\n')
	{
		line[i] = total_chars[i];
		i++;
	}
	if (total_chars[i] == '\n')
		line[i] = '\n';
	return (line);
}
