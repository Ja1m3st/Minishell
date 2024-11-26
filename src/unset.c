/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 11:54:29 by jaimesan          #+#    #+#             */
/*   Updated: 2024/11/26 12:31:56 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset(t_mini *mini)
{
	int	len;
	int i;
	int j;
	char **new_env;

	i = 0;
	if (mini->cmds[1])
	{
		len = ft_strlen(mini->cmds[1]);

		while (mini->env[i])
			i++;

		new_env = malloc(sizeof(char *) * i);
		if (!new_env)
			return ;
		i = 0;
		j = 0;
		while (mini->env[i])
		{
			if (ft_strncmp(mini->env[i], mini->cmds[1], len) == 0 && mini->env[i][len] == '=')
			{
/* 				free(mini->env[i]); */
				mini->env[i] = NULL;
				i++;
				continue ;
			}
			new_env[j] = mini->env[i];
			i++;
			j++;
		}
		new_env[j] = NULL;
/* 		free(mini->env); */
		mini->env = NULL;
		mini->env = new_env;
	}
}