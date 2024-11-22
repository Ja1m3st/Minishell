/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:43:39 by jaimesan          #+#    #+#             */
/*   Updated: 2024/11/22 13:39:57 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main()
{
    	t_mini       mini;
	
	while (1)
	{
		mini.input = readline("➜ ~ ");
		if (!mini.input)
			break;
		if (*mini.input)
			add_history(mini.input);
		get_commands(&mini);
		free(mini.input);
	}
	rl_clear_history();
    return (0);
}