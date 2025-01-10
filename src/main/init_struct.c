/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 14:59:33 by ctommasi          #+#    #+#             */
/*   Updated: 2025/01/10 11:20:11 by jaimesan         ###   ########.fr       */
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
	mini->state.double_quote = 0;
	mini->state.single_quote = 0;
	mini->state.result = 0;
	if (!mini->commands)
		return ;
	*mini->commands = NULL;
	init_fds(mini);
	dup_env(mini, env);
	setup_signals();
	disable_echoctl();
	get_env_name(mini);
}
