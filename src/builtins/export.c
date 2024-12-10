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

void	export(t_mini *mini, t_token *token)
{
	int		i;
	int		j;

	if (!token->cmd[1])
		return ;
	i = 1;
	while (token->cmd[i])
	{
		if (check_valid_export(mini, token))
		{
			write(1, "Bad Assignment!\n", 16);
			return ;
		}
		j = export_exists(mini, token);
		if (j == -1)
			new_export(mini, token);
		else
		{
			free(mini->env[j]);
			mini->env[j] = ft_strdup(token->cmd[i]);
		}
		j = -1;
		i++;
	}
	
}

int	export_exists(t_mini *mini, t_token *token)
{
	int		i;
	int		len;
	char	*var_name;

	i = 0;
	while (token->cmd[1][i] != '=')
		i++;
	var_name = malloc(i + 1 * sizeof(char));
	if (!var_name)
		return (-1);
	ft_strlcpy(var_name, token->cmd[1], i + 1);
	i = 0;
	len = ft_strlen(var_name);
	if (len == 1)
		len = ft_strlen(mini->env[i]);
	while (i < array_len(mini->env))
	{
		if (ft_strncmp(mini->env[i], var_name, len) == 0)
			return (free(var_name), i);
		i++;
	}
	return (free(var_name), -1);
}

void	new_export(t_mini *mini, t_token *token)
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
	new_env[len] = ft_strdup(token->cmd[1]);
	new_env[len + 1] = NULL;
	free_arr(mini->env);
	mini->env = new_env;
}

int	check_valid_export(t_mini *mini, t_token *token)
{
	int	i;

	i = 0;
	while (token->cmd[1][i] != '=')
	{
		if (i == 0 && ft_isdigit(token->cmd[1][i]))
			return (1);
		if (!(ft_isalnum(token->cmd[1][i]) || token->cmd[1][i] == '_'))
			return (1);
		i++;
	}
	if (token->cmd[1][i] == '=')
		return (0);
	return (1);
}
