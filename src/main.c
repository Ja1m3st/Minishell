/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:43:39 by jaimesan          #+#    #+#             */
/*   Updated: 2024/11/25 15:46:37 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_mini	mini;
	char	*read;

	if (argc != 1)
		return (0);
	mini.env = env;
	(void)argv;
	init_struct(&mini);
	get_full_name(&mini);
	while (1)
	{
		read = read_line(&mini);
		mini.input = readline(read);
		if (!mini.input)
			break ;
		if (*mini.input)
			add_history(mini.input);
		mini.cmds = ft_split(mini.input, ' ');
		get_commands(&mini);
		free(mini.input);
		free_char_array(mini.cmds);
	}
	free(mini.full_name);
	free(mini.log_name);
	free(mini.sesion_name);
	free(read);
	rl_clear_history();
	return (0);
}
