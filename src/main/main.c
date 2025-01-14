/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:43:39 by jaimesan          #+#    #+#             */
/*   Updated: 2025/01/14 13:51:11 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_mini	mini;

	if (argc != 1)
		return (1);
	init_struct(&mini, argv, env);
	while (1)
	{
		mini.input = readline(join_env_name(&mini));
		if (!mini.input)
			break ;
		if (*mini.input == '\0')
		{
			free(mini.input);
			continue ;
		}
		if (*mini.input)
			add_history(mini.input);
		process_commands(&mini);
		tokenize_commands(&mini, mini.mini_cmds, NULL);
		if (!check_quotation(&mini))
			continue ;
		execute_commands(&mini);
		free_main(&mini);
	}
	return (error(&mini, '!'), 0);
}
