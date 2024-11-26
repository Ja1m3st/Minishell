/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 11:54:29 by jaimesan          #+#    #+#             */
/*   Updated: 2024/11/26 13:38:06 by jaimesan         ###   ########.fr       */
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
	int		len;
	int		i;
	int		j;
	int		cmd_len;

	if (!mini->cmds[1] || find_env_variable(mini->env, mini->cmds[1]) == NULL)
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
		if (ft_strncmp(mini->env[i], mini->cmds[1], cmd_len) == 0
			&& mini->env[i][cmd_len] == '=')
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
