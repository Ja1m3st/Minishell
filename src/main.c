/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:43:39 by jaimesan          #+#    #+#             */
/*   Updated: 2024/11/22 14:44:29 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main()
{
    t_mini       mini;
	HIST_ENTRY	**hist_entries;

	while (1)
	{
		mini.input = readline("➜ ~ ");
		if (!mini.input)
			break ;
		if (*mini.input)
			add_history(mini.input);
		if (ft_strcmp(mini.input, "history") == 0)
			print_history(hist_entries);
		free(mini.input);
	}
	rl_clear_history();
    return (0);
}