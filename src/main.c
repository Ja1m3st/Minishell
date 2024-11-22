/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:43:39 by jaimesan          #+#    #+#             */
/*   Updated: 2024/11/22 17:51:51 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **env)
{
	t_mini       mini;

	if (argc != 1)
		return (0);
	mini.env = env;
	(void)argv;
	get_full_name(&mini);
	while (1)
	{
		mini.input = readline(ft_strjoin(mini.full_name, "~$ "));
		if (!mini.input)
			break ;
		if (*mini.input)
			add_history(mini.input);
		save_cmds(&mini);
		get_commands(&mini);
		free(mini.input);
	}
	rl_clear_history();
	return (0);
}
