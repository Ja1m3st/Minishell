/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 11:54:29 by jaimesan          #+#    #+#             */
/*   Updated: 2024/11/26 13:11:47 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset(t_mini *mini)
{
	char	**new_env;
	int		len;
	int		i;
	int		j;
	int		cmd_len;

	if (!mini->cmds[1])
		return ;
	if (!getenv(mini->cmds[1]))
		return ;
	len = array_len(mini->env);
	cmd_len = ft_strlen(mini->cmds[1]);

	new_env = malloc(len * sizeof(char *));
	if (!new_env)
		error(mini, 'M');

	i = 0;
	j = 0;
	while (i < len)
	{
		if (ft_strncmp(mini->env[i], mini->cmds[1], cmd_len) == 0 && mini->env[i][cmd_len] == '=')
		{
			i++;
			continue ;
		}
		new_env[j++] = ft_strdup(mini->env[i]);
		i++;
	}
	new_env[j] = NULL;
	free_arr(mini->env);
	mini->env = new_env;
}