/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 17:10:19 by ctommasi          #+#    #+#             */
/*   Updated: 2024/11/26 12:00:52 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export(t_mini *mini)
{
	char	**new_env;
	int		len;
	int		i;

	len = array_len(mini->env);
	new_env = malloc((len + 2) * sizeof(char *));
	if (!new_env)
		error(mini, 'M');
	i = 0;
	while (i < len)
	{
		new_env[i] = ft_strdup(mini->env[i]);
		i++;
	}
	new_env[len] = ft_strdup(mini->cmds[1]);
	new_env[len + 1] = NULL;
	free_arr(mini->env);
	mini->env = new_env;
}
