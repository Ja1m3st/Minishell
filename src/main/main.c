/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:43:39 by jaimesan          #+#    #+#             */
/*   Updated: 2024/12/18 12:15:16 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_mini	mini;
	char	*env_name;

	if (argc != 1)
		return (1);
	init_struct(&mini, argv, env);
	while (1)
	{
		env_name = join_env_name(&mini);
		mini.input = readline(env_name);
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
		if (!check_quotation(&mini))
			continue ;
		tokenize_commands(&mini, mini.mini_cmds);
		execute_commands(&mini);
		free_main(&mini);
	}
	return (error(&mini, '!'), 0);
}
