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
	mini->env = NULL;
	mini->full_cmds = NULL;
	mini->env_name = NULL;
	mini->full_name = NULL;
	mini->log_name = NULL;
	mini->path = NULL;
	mini->sesion_name = NULL;
	mini->input = NULL;
	mini->oldpath = NULL;
	mini->full_path = NULL;
	mini->newline = 0;
	mini->full_path = NULL;
	mini->split_full_cmds = NULL;
	mini->d_quote = 0;
	mini->s_quote = 0;
	dup_env(mini, env);
	setup_signals();
	disable_echoctl();
	get_env_name(mini);
	mini->list = malloc(sizeof(t_token *));
	if (!mini->list)
		return ;
	*(t_token **)mini->list = NULL;
	mini->do_swap = 0;
}
