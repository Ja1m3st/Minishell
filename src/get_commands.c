/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 13:30:27 by jaimesan          #+#    #+#             */
/*   Updated: 2024/11/22 15:52:50 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	get_commands(t_mini *mini)
{
	if  (mini->cmds[0])
	{
		if (!ft_strcmp(mini->cmds[0], "history"))
			print_history();
		if (!ft_strcmp(mini->cmds[0], "env"))
			print_env(mini);
		if (!ft_strcmp(mini->cmds[0], "pwd"))
			print_pwd(mini);
	}
}
