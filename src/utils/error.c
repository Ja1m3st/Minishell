/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 15:36:54 by ctommasi          #+#    #+#             */
/*   Updated: 2024/11/28 15:53:42 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error(t_mini *mini, char c)
{
	if (c == 'M')
		write(1, "Malloc Error!\n", 14);
	free_mini(mini);
	if (c == '!')
		exit(EXIT_SUCCESS);
	exit(EXIT_FAILURE);
}

void	free_mini(t_mini *mini)
{
	int		i;

	if (mini->full_name)
		free(mini->full_name);
	if (mini->log_name)
		free(mini->log_name);
	if (mini->sesion_name)
		free(mini->sesion_name);
	if (mini->env)
		free_arr(mini->env);
	if (mini->oldpath)
		free(mini->oldpath);
	if (mini->dquote)
		free(mini->dquote);
	if (mini->full_path)
		free(mini->full_path);
	if (mini->env)
		free(mini->env_name);
	if (mini->split_full_cmds)
		free_arr(mini->split_full_cmds);
}
