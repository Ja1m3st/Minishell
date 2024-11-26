/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 13:22:34 by jaimesan          #+#    #+#             */
/*   Updated: 2024/11/26 16:40:03 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_arr(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	free(array);
	array = NULL;
}

int	array_len(char **array)
{
	int	i;

	i = 0;
	while (array && array[i])
		i++;
	return (i);
}

char	*find_path(t_mini *mini, char *path)
{
	int		len;
	int		i;
	int		oldpath_len;
	char	*find;

	len = array_len(mini->env);
	i = 0;
	while (i < len)
	{
		if (ft_strncmp(mini->env[i], path, 5) == 0)
		{
			find = ft_strrchr(mini->env[i], '=');
			find++;
			return (find);
		}
		i++;
	}
	return (NULL);
}

char	*find_var(char	*str, char c)
{
	char	*var_name;

	var_name = ft_strchr(str, c);
	var_name++;
	return (var_name);
}
