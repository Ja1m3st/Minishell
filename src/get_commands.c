/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 13:30:27 by jaimesan          #+#    #+#             */
/*   Updated: 2024/11/26 11:56:59 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_commands(t_mini *mini)
{
	if (mini->cmds[0])
	{
		if (!ft_strcmp(mini->cmds[0], "history"))
			print_history();
		if (!ft_strcmp(mini->cmds[0], "env"))
			print_env(mini);
		if (!ft_strcmp(mini->cmds[0], "echo"))
			echo(mini);
		if (!ft_strcmp(mini->cmds[0], "pwd"))
			print_pwd();
		if (!ft_strcmp(mini->cmds[0], "cd"))
			cd(mini);
		if (!ft_strcmp(mini->cmds[0], "export"))
			export(mini);
		if (!ft_strcmp(mini->cmds[0], "unset"))
			unset(mini);
		if (!ft_strcmp(mini->cmds[0], "exit"))
		{
			write(1, "exit\n", 5);
			exit(EXIT_SUCCESS);
		}
	}
}
