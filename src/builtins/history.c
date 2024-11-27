/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 12:59:57 by jaimesan          #+#    #+#             */
/*   Updated: 2024/11/25 11:22:43 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_history(void)
{
	int			i;
	HIST_ENTRY	**hist_entries;

	i = 0;
	hist_entries = history_list();
	if (hist_entries)
	{
		while (hist_entries[i])
		{
			printf("%d %s\n", i + history_base, hist_entries[i]->line);
			i++;
		}
	}
}
