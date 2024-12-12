/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 11:54:29 by jaimesan          #+#    #+#             */
/*   Updated: 2024/12/12 15:01:31 by jaimesan         ###   ########.fr       */
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

char	**ft_new_env(t_mini *mini, char *str, char **new_env)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < array_len(mini->env))
	{
		if (ft_strncmp(mini->env[i], str,
				ft_strlen(str)) == 0
			&& mini->env[i][ft_strlen(str)] == '=')
		{
			i++;
			continue ;
		}
		new_env[j++] = ft_strdup(mini->env[i++]);
	}
	new_env[j] = NULL;
	return (new_env);
}

void	unset(t_mini *mini)
{
	char		**new_env;
	static int	x;
	char		*str;

	x++;
	str = ft_strdelchar(mini->mini_cmds[x], "'\"");
	if (!str || find_env_variable(mini->env, str) == NULL)
		return (free(str));
	new_env = malloc(array_len(mini->env) * sizeof(char *));
	if (!new_env)
		error(mini, 'M');
	new_env = ft_new_env(mini, str, new_env);
	free(str);
	free_arr(mini->env);
	mini->env = new_env;
	if (mini->mini_cmds[x + 1] && !ft_strchr(mini->mini_cmds[x + 1], '|')
		&& mini->mini_cmds[x + 1] != NULL)
		unset(mini);
}
