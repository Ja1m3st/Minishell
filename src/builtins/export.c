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

	if (check_valid_export(mini))
	{
		write(1, "Bad Assignment!\n", 16);
		return ;
	}
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
