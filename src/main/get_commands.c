/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 13:30:27 by jaimesan          #+#    #+#             */
/*   Updated: 2024/12/02 15:17:38 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_commands(t_mini *mini)
{
	save_cmds(mini);
	if (mini->total_args == 1)
	{
		mini->cmds = ft_split(mini->split_full_cmds[0], ' ');
		if (!ft_strcmp(mini->cmds[0], "history"))
			print_history();
		else if (!ft_strcmp(mini->cmds[0], "env"))
			print_env(mini);
		else if (!ft_strcmp(mini->cmds[0], "echo"))
			echo(mini);
		else if (!ft_strcmp(mini->cmds[0], "pwd"))
			print_pwd();
		else if (!ft_strcmp(mini->cmds[0], "cd"))
			cd(mini);
		else if (!ft_strcmp(mini->cmds[0], "export"))
			export(mini);
		else if (!ft_strcmp(mini->cmds[0], "unset"))
			unset(mini);
		else if (!ft_strncmp(mini->cmds[0], "$", 1))
		{
			if (get_var(mini) != NULL)
				printf("%s\n", get_var(mini));
		}
		else if (!ft_strcmp(mini->cmds[0], "exit"))
			error(mini, '!');
		else
			get_terminal_commands(mini);
		free_arr(mini->cmds);
	}
	else
		pipex(mini);
}



void	get_commands(t_mini *mini)
{
	save_cmds(mini);
	if (mini->split_full_cmds[0])
		pipex(mini);
}
