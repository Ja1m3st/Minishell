/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:43:39 by jaimesan          #+#    #+#             */
/*   Updated: 2024/12/16 11:48:54 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_mini	mini;
	char	*env_name;
	int i;

	if (argc != 1)
		return (1);
	init_struct(&mini, argv, env);
	while (1)
	{
		i = 0;
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
		while (mini.mini_cmds[i] && !ft_strchr(mini.mini_cmds[i], '~'))
		{
			if (mini.mini_cmds[i][0] == '"')
				process_input_multi(mini.mini_cmds[i++], '"');
			else
				process_input_single(mini.mini_cmds[i++], '\'');
		}
		tokenize_commands(&mini, mini.mini_cmds);
		print_tree_structure(&mini);
		execute_commands(&mini);
		free_main(&mini);
	}
	error(&mini, '!');
	return (0);
}
// while (mini.mini_cmds[i] && !ft_strchr(mini.mini_cmds[i], '~'))
// 	ft_ptrdelchar(mini.mini_cmds[i++], "\'\"");