/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_valid_digits.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctommasi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 13:13:11 by ctommasi          #+#    #+#             */
/*   Updated: 2024/10/30 13:13:13 by ctommasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_check_valid_digits(char **temp, int j)
{
	int	k;

	k = 0;
	while (temp[j][k])
	{
		if (ft_atoi(temp[j]) > 2147483647 || ft_atoi(temp[j]) < -2147483648)
			return (1);
		if (temp[j][k] == '-' || temp[j][k] == '+')
			k++;
		if (!ft_isdigit(temp[j][k]))
			return (1);
		k++;
	}
	return (0);
}
