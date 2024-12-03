/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:43:39 by jaimesan          #+#    #+#             */
/*   Updated: 2024/12/02 15:13:35 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_mini	mini;
	char	*env_name;

	if (argc != 1)
		return (0);
	init_struct(&mini, argv, env);
	get_env_name(&mini);
	while (1)
	{
		env_name = join_env_name(&mini);
		mini.input = readline(env_name);
		if (!mini.input)
			break ;
		if (*mini.input)
			add_history(mini.input);
		mini.full_cmds = mini.input;
		mini.cmds = ft_split(mini.full_cmds, ' ');
		init_commands(&mini, mini.cmds);
		// get_commands(&mini);
		free(mini.input);
	}
	error(&mini, '!');
	rl_clear_history();
	return (0);
}
