/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:43:39 by jaimesan          #+#    #+#             */
/*   Updated: 2024/12/13 12:59:11 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_mini	mini;
	int		i;
	char	*env_name;

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
		if (*mini.input)
			add_history(mini.input);
		process_commands(&mini);
		tokenize_commands(&mini, mini.mini_cmds);
		execute_commands(&mini);
		free_arr_cmds(mini.mini_cmds);
		mini.mini_cmds = NULL;
		free_commands(&mini);
		free(mini.input);
	}
	return (error(&mini, '!'), 0);
}
// while (mini.mini_cmds[i] && !ft_strchr(mini.mini_cmds[i], '~'))
// 	ft_ptrdelchar(mini.mini_cmds[i++], "\'\"");