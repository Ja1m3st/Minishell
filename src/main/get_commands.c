/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 13:30:27 by jaimesan          #+#    #+#             */
/*   Updated: 2024/11/28 16:08:30 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_commands(t_mini *mini)
{
	if (mini->cmds[0] && check_tub(mini) == 1)
	{
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
	}
	else if (check_tub(mini) == 0)
	{
		pipex(mini);
	}
}
