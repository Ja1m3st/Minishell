/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 12:59:57 by jaimesan          #+#    #+#             */
/*   Updated: 2024/11/22 13:26:46 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_history(t_mini *mini)
{
	int i;

	i = 0;
	mini->hist_entries = history_list();
	if (mini->hist_entries)
	{
		while(mini->hist_entries[i])
		{
			printf("%d %s\n", i + history_base, mini->hist_entries[i]->line);
			i++;
		}
	}
}
