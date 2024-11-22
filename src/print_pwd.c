/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_pwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 15:53:03 by jaimesan          #+#    #+#             */
/*   Updated: 2024/11/22 16:38:29 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_pwd(t_mini *mini)
{
	int		i;
	char	*str;

	i = 0;
	str = NULL;
	while (mini->env[i])
	{
		str = ft_split(mini->env[i], '=')[0];
		if (str && !ft_strcmp(str, "PWD"))
		{
			printf("%s\n", ft_split(mini->env[i], '=')[1]);
			free(str);
			break ;
		}
		free(str);
		i++;
	}
}
