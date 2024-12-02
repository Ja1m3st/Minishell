/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 11:54:29 by jaimesan          #+#    #+#             */
/*   Updated: 2024/12/02 16:07:21 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_env_variable(char **env, const char *key)
{
	int	i;
	int	key_len;

	i = 0;
	if (!env || !key)
		return (NULL);
	key_len = ft_strlen(key);
	while (env[i])
	{
		if (ft_strncmp(env[i], key, key_len) == 0 && env[i][key_len] == '=')
			return (env[i]);
		i++;
	}
	return (NULL);
}

void	unset(t_mini *mini)
{
	char	**new_env;
	int		i;
	int		j;

	if (!mini->cmds[1] || find_env_variable(mini->env, mini->cmds[1]) == NULL)
		return ;
	new_env = malloc(array_len(mini->env) * sizeof(char *));
	if (!new_env)
		error(mini, 'M');
	i = 0;
	j = 0;
	while (i < array_len(mini->env))
	{
		if (ft_strncmp(mini->env[i], mini->cmds[1],
				ft_strlen(mini->cmds[1])) == 0
			&& mini->env[i][ft_strlen(mini->cmds[1])] == '=')
		{
			i++;
			continue ;
		}
		new_env[j++] = ft_strdup(mini->env[i++]);
	}
	new_env[j] = NULL;
	free_arr(mini->env);
	mini->env = new_env;
}
