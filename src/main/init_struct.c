/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 14:59:33 by ctommasi          #+#    #+#             */
/*   Updated: 2024/12/02 12:11:33 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_struct(t_mini *mini, char **argv, char **env)
{
	(void)argv;
	mini->infile = STDIN_FILENO;
	mini->outfile = STDOUT_FILENO;
	mini->fd[0] = 0;
	mini->fd[1] = 1;
	mini->temp_fd = -1;
	mini->env = NULL;
	mini->env_name = NULL;
	mini->full_name = NULL;
	mini->log_name = NULL;
	mini->path = NULL;
	mini->sesion_name = NULL;
	mini->input = NULL;
	mini->oldpath = NULL;
	mini->full_path = NULL;
	dup_env(mini, env);
	setup_signals();
	disable_echoctl();
	get_env_name(mini);
	mini->commands = malloc(sizeof(t_token *));
	if (!mini->commands)
		return ;
	*mini->commands = NULL;
	mini->is_last_cmd = 0;
}
