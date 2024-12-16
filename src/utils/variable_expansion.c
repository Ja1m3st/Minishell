/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctommasi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 13:15:59 by ctommasi          #+#    #+#             */
/*   Updated: 2024/12/16 13:16:01 by ctommasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	variable_expansion(t_mini *mini)
{
	int	i;
	int	j;
	int	k;
	int	l;
	char	*res = NULL;
	char	*var = NULL;
	char	*value = NULL;

	i = 0;
	while (mini->mini_cmds[i])
	{
		j = 0;
		res = ft_strdup("");
		l = 0;
		while (mini->mini_cmds[i][j])
		{
			if (mini->mini_cmds[i][j] && mini->mini_cmds[i][j] == '$')
			{

				var = ft_strdup("");
				j++;
				k = 0;
				while (mini->mini_cmds[i][j] != '\0' && mini->mini_cmds[i][j] && mini->mini_cmds[i][j] != ' ' && mini->mini_cmds[i][j] != '$')
				{
					var = ft_realloc(var, ft_strlen(var), ft_strlen(var) + 2);
					var[k++] = mini->mini_cmds[i][j];
					var[k] = '\0';
					j++;
				}
				value = get_var_value(mini, var);
				if (value)
				{
					res = ft_strjoin_free(res, value);
					free(var);
					var = NULL;
					value = NULL;
					k = 0;
					continue;
				}
			}
			else
			{
				res = ft_realloc(res, ft_strlen(res), ft_strlen(res) + 2);
				res[l++] = mini->mini_cmds[i][j];
				res[l] = '\0';
				
			}
			j++;
		}
		free(mini->mini_cmds[i]);
		mini->mini_cmds[i] = ft_strdup(res);
		free(res);
		i++;
	}
}

char	*get_var_value(t_mini *mini, char *mini_cmds)
{
	int		i;
	int		arr_len;
	char	*value;

	arr_len = array_len(mini->env);
	if (ft_strlen(mini_cmds) == 1)
		return (NULL);
	i = 0;
	while (i < arr_len)
	{
		if (ft_strncmp(mini->env[i], mini_cmds, ft_strlen(mini_cmds)) == 0)
		{
			value = ft_strchr(mini->env[i], '=');
			value++;
			return (value);
		}
		i++;
	}
	return (0);
}
