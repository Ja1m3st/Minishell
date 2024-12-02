/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 13:30:27 by jaimesan          #+#    #+#             */
/*   Updated: 2024/12/02 12:23:06 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	built_int(int in_fd, int mini_fd[], int i, t_mini *mini)
{
	if (!ft_strcmp(mini->cmds[0], "history"))
		print_history();
	else if (!ft_strcmp(mini->cmds[0], "env"))
		print_env(mini);
	else if (!ft_strcmp(mini->cmds[0], "echo"))
		echo(mini);
	else if (!ft_strcmp(mini->cmds[0], "cd"))
		cd(mini);
	else if (!ft_strcmp(mini->cmds[0], "pwd"))
		print_pwd(mini);
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
	{
		write(1, "exit\n", 5);
		exit(EXIT_SUCCESS);
	}
	else
	{
		exeve_pipe(in_fd, mini_fd, i, mini);
	}
}

void	get_commands(t_mini *mini)
{
	save_cmds(mini);
	if (mini->split_full_cmds[0])
		pipex(mini);
}
