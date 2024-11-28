/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_terminal_commands.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 12:26:36 by ctommasi          #+#    #+#             */
/*   Updated: 2024/11/28 12:47:52 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_terminal_commands(t_mini *mini)
{
	if (mini->full_path)
		free(mini->full_path);
	mini->full_path = ft_strjoin("/usr/bin/", mini->cmds[0]);
	if (!mini->full_path)
		return ;
	mini->pid = fork();
	if (mini->pid == -1)
		return ;
	if (mini->pid == 0)
	{
		execve(mini->full_path, mini->cmds, mini->env);
		return ;
	}
	waitpid(mini->pid, NULL, 0);
}
