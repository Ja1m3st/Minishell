/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 16:07:14 by jaimesan          #+#    #+#             */
/*   Updated: 2024/11/28 16:07:24 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	save_cmds(t_mini *mini)
{
	int i;

	i = 0;
	if (mini->split_full_cmds)
		free_arr(mini->split_full_cmds);
	mini->split_full_cmds = ft_split(mini->full_cmds, '|');
	while (mini->split_full_cmds[i] != NULL)
		i++;
	mini->total_args = i;
}

int	check_tub(t_mini *mini)
{
	int i;

	i = 0;
	while (mini->cmds[i] != NULL)
	{
		if (!ft_strcmp(mini->cmds[i], "|"))
		{
			save_cmds(mini);
			return (0);
		}
		i++;
	}
	return (1);
}