/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctommasi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 12:32:11 by ctommasi          #+#    #+#             */
/*   Updated: 2024/11/01 12:32:12 by ctommasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_read_line(int fd, char *total_chars)
{
	char	*temp;
	ssize_t	bytes_read;

	if (total_chars == NULL)
		total_chars = ft_calloc_z(1, 1);
	if (total_chars == NULL)
		return (NULL);
	temp = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (temp == NULL)
		return (free(total_chars), NULL);
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, temp, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free(temp), free(total_chars), NULL);
		temp[bytes_read] = '\0';
		total_chars = ft_strjoin_free(total_chars, temp);
		if (total_chars == NULL)
			return (free(temp), free(total_chars), NULL);
		if (ft_strchr(total_chars, '\n'))
			break ;
	}
	return (free(temp), total_chars);
}
