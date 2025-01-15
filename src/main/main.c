/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:43:39 by jaimesan          #+#    #+#             */
/*   Updated: 2025/01/15 13:53:44 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_status;

int	check_input(char *str)
{
	if (*str == '\0')
		return (free(str), 1);
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
		if (main_commands(&mini))
			continue ;
		execute_commands(&mini);
		free_main(&mini);
	}
	return (error(&mini, '!'), 0);
}

int	main_commands(t_mini *mini)
{
	if (*mini->input == '\0')
	{
		free(mini->input);
		return (1);
	}
	process_commands(mini);
	if (tokenize_commands(mini, mini->mini_cmds, NULL))
	{
		free_main(mini);
		return (1);
	}
	if (check_quotation(mini))
	{
		free_main(mini);
		return (1);
	}
	return (0);
}
