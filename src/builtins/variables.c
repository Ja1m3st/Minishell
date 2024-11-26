/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctommasi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 12:57:14 by ctommasi          #+#    #+#             */
/*   Updated: 2024/11/26 12:57:15 by ctommasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_var(t_mini *mini)
{
	int		i;
	int		len;
	int		oldpath_len;
	char	*find = NULL;

	len = array_len(mini->env);
	i = 0;
	
	while (i < len)
	{
		char *find3 = ft_strchr(mini->cmds[0], '$');
		find3++;
		char *find4 = ft_substr(mini->env[68], 0, ft_strlen(ft_strchr(mini->cmds[0], '$') + 1));
		if (ft_strcmp(find4, find3) == 0)
		{
			find = ft_strchr(mini->env[i], '=');
			find++;
			return (find);
		}
		i++;
	}
	return (NULL);
}
