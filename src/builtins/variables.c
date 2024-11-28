/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctommasi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 12:57:14 by ctommasi          #+#    #+#             */
/*   Updated: 2024/11/26 12:57:15 by ctommasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_var(t_mini *mini)
{
	int		i;
	int		arr_len;
	char	*value;
	char	*var_name;

	arr_len = array_len(mini->env);
	var_name = find_var(mini->cmds[0], '$');
	if (ft_strlen(mini->cmds[0]) == 1)
		return (NULL);
	i = 0;
	while (i < arr_len)
	{
		if (ft_strncmp(mini->env[i], var_name, ft_strlen(var_name)) == 0)
		{
			value = ft_strchr(mini->env[i], '=');
			value++;
			return (value);
		}
		i++;
	}
	return (0);
}
