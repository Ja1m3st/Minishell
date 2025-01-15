/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:43:39 by jaimesan          #+#    #+#             */
/*   Updated: 2025/01/15 13:20:16 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_status;

int	check_input(char *str)
{
	if (*str == '\0')
	{
		free(str);
		return (1);
	}
	return (0);
}

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
		if (check_input(mini.input))
			continue ;
		if (*mini.input)
			add_history(mini.input);
		process_commands(&mini);
		tokenize_commands(&mini, mini.mini_cmds, NULL);
		print_tree_structure(&mini);
		if (!check_quotation(&mini))
			continue ;
		execute_commands(&mini);
		free_main(&mini);
	}
	return (error(&mini, '!'), 0);
}
