/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 13:30:27 by jaimesan          #+#    #+#             */
/*   Updated: 2024/12/02 16:10:26 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_commands(t_mini *mini)
{
	int	i;

	i = 0;
	if (mini->split_full_cmds)
		free_arr(mini->split_full_cmds);
	mini->split_full_cmds = ft_split(mini->full_cmds, '|');
	while (mini->split_full_cmds[i] != NULL)
		i++;
	mini->total_args = i;
	execute_builtins(mini, 0);
}

void	execute_builtins(t_mini *mini, int mod)
{
	if (mod == 1)
	{
		cmds(mini, mod);
		exit(EXIT_SUCCESS);
		return ;
	}
	if (mini->total_args == 1)
	{
		mini->cmds = ft_split(mini->split_full_cmds[0], ' ');
		cmds(mini, mod);
		free_arr(mini->cmds);
	}
	else
		pipex(mini);
}

void	cmds(t_mini *mini, int mod)
{
	if (!ft_strcmp(mini->cmds[0], "history"))
		print_history();
	else if (!ft_strcmp(mini->cmds[0], "env"))
		print_env(mini);
	else if (!ft_strcmp(mini->cmds[0], "echo"))
		echo(mini);
	else if (!ft_strcmp(mini->cmds[0], "pwd"))
		print_pwd(mini);
	else if (!ft_strcmp(mini->cmds[0], "cd"))
		cd(mini);
	else if (!ft_strcmp(mini->cmds[0], "export"))
		export(mini);
	else if (!ft_strcmp(mini->cmds[0], "unset"))
		unset(mini);
	else if (!ft_strncmp(mini->cmds[0], "$", 1))
		printf("%s\n", get_var(mini));
	else if (!ft_strcmp(mini->cmds[0], "exit"))
		error(mini, '!');
	else
	{
		if (mod == 0)
			get_terminal_commands(mini);
	}
}
