/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctommasi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 14:34:47 by ctommasi          #+#    #+#             */
/*   Updated: 2024/11/28 14:34:48 by ctommasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	setup_signals(void)
{
	struct sigaction	ctrl_c;
	struct sigaction	ctrl_backslash;

	ft_memset(&ctrl_c, 0, sizeof(ctrl_c));
	ft_memset(&ctrl_backslash, 0, sizeof(ctrl_backslash));
	ctrl_c.sa_handler = &handle_sigint;
	ctrl_c.sa_flags = SA_RESTART;
	ctrl_backslash.sa_handler = &handle_sigquit;
	ctrl_backslash.sa_flags = SA_RESTART;
	if (sigaction(SIGINT, &ctrl_c, NULL) == -1)
		perror("sigaction");
	if (sigaction(SIGQUIT, &ctrl_backslash, NULL) == -1)
		perror("sigaction");
}

void	handle_sigint(int signal)
{
	(void)signal;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_sigquit(int signal)
{
	(void)signal;
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}