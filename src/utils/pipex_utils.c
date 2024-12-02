/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 16:07:14 by jaimesan          #+#    #+#             */
/*   Updated: 2024/12/02 13:26:01 by jaimesan         ###   ########.fr       */
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