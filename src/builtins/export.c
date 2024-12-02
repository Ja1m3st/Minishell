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
	int		i;

	if (!mini->cmds[1])
		return ;
	if (check_valid_export(mini))
	{
		write(1, "Bad Assignment!\n", 16);
		return ;
	}
	i = export_exists(mini);
	if (i == -1)
		new_export(mini);
	else
	{
		free(mini->env[i]);
		mini->env[i] = ft_strdup(mini->cmds[1]);
	}
}

int	export_exists(t_mini *mini)
{
	int		i;
	int		arr_len;
	char	*var_name;

	i = 0;
	while (mini->cmds[1][i] != '=')
		i++;
	var_name = malloc(i + 1 * sizeof(char));
	if (!var_name)
		return (-1);
	ft_strlcpy(var_name, mini->cmds[1], i + 1);
	arr_len = array_len(mini->env);
	i = 0;
	while (i < arr_len)
	{
		if (ft_strncmp(mini->env[i], var_name, ft_strlen(var_name)) == 0)
			return (free(var_name), i);
		i++;
	}
	return (free(var_name), -1);
}

void	new_export(t_mini *mini)
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

int	check_valid_export(t_mini *mini)
{
	int	i;

	i = 0;
	while (mini->cmds[1][i] != '=')
	{
		if (i == 0 && ft_isdigit(mini->cmds[1][i]))
			return (1);
		if (!(ft_isalnum(mini->cmds[1][i]) || mini->cmds[1][i] == '_'))
			return (1);
		i++;
	}
	if (mini->cmds[1][i] == '=')
		return (0);
	return (1);
}
