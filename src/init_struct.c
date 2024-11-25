/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctommasi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 14:59:33 by ctommasi          #+#    #+#             */
/*   Updated: 2024/11/25 14:59:34 by ctommasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_struct(t_mini *mini, char **argv, char **env)
{
	mini->infile = STDIN_FILENO;
	mini->outfile = STDOUT_FILENO;
	mini->env = env;
	(void)argv;
	mini->env_name = NULL;
	mini->full_name = NULL;
	mini->log_name = NULL;
	mini->path = NULL;
	mini->sesion_name = NULL;
	mini->input = NULL;
}
