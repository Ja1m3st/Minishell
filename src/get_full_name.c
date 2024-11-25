/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_full_name.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 16:57:39 by jaimesan          #+#    #+#             */
/*   Updated: 2024/11/25 11:22:06 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_name(t_mini *mini)
{
	int		i;
	char	*str;

	str = NULL;
	i = 0;
	while (mini->env[i++])
	{
		str = ft_split(mini->env[i], '=')[0];
		if (str && !ft_strcmp(str, "LOGNAME"))
		{
			mini->log_name = ft_split(mini->env[i], '=')[1];
			free(str);
			break ;
		}
		free(str);
	}
}

void	get_sesion_name(t_mini *mini)
{
	int		i;
	char	*str;

	str = NULL;
	i = 0;
	while (mini->env[i++])
	{
		str = ft_split(mini->env[i], '=')[0];
		if (str && !ft_strcmp(str, "SESSION_MANAGER"))
		{
			str = ft_split(mini->env[i], '=')[1];
			mini->sesion_name = ft_split(ft_split(str, '/')[1], '.')[0];
			free(str);
			break ;
		}
		free(str);
	}
}

void	get_full_name(t_mini *mini)
{
	get_name(mini);
	get_sesion_name(mini);
	mini->log_name = ft_strjoin(mini->log_name, "@");
	mini->full_name = ft_strjoin(mini->log_name, mini->sesion_name);
}
