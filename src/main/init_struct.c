/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 14:59:33 by ctommasi          #+#    #+#             */
/*   Updated: 2024/12/12 15:54:57 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_struct(t_mini *mini, char **argv, char **env)
{
	(void)argv;
	mini->input = NULL;
	mini->mini_cmds = NULL;
	mini->env = NULL;
	mini->log_name = NULL;
	mini->sesion_name = NULL;
	mini->full_name = NULL;
	mini->path = NULL;
	mini->env_name = NULL;
	mini->oldpath = NULL;
	mini->full_path = NULL;
	mini->quote_types = NULL;
	mini->is_last_cmd = 0;
	mini->commands = malloc(sizeof(t_token *));
	if (!mini->commands)
		return ;
	*mini->commands = NULL;
	init_fds(mini);
	dup_env(mini, env);
	setup_signals();
	disable_echoctl();
	get_env_name(mini);
}

void	init_fds(t_mini *mini)
{
	mini->infile = STDIN_FILENO;
	mini->outfile = STDOUT_FILENO;
	mini->fd[0] = -1;
	mini->fd[1] = -1;
	mini->temp_fd = -1;
}
