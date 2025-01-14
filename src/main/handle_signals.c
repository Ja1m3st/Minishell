/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 14:34:47 by ctommasi          #+#    #+#             */
/*   Updated: 2025/01/14 16:59:39 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	setup_signals(void)
{
	struct sigaction	ctrl_c;
	struct sigaction	ctrl_d;
	struct sigaction	ctrl_backslash;

	ft_memset(&ctrl_c, 0, sizeof(ctrl_c));
	ft_memset(&ctrl_d, 0, sizeof(ctrl_d));
	ft_memset(&ctrl_backslash, 0, sizeof(ctrl_backslash));
	ctrl_c.sa_handler = &handle_sigint;
	ctrl_c.sa_flags = SA_RESTART;
	ctrl_d.sa_handler = &handle_sigquit;
	ctrl_d.sa_flags = SA_RESTART;
	ctrl_backslash.sa_handler = SIG_IGN;
	ctrl_backslash.sa_flags = 0;
	if (sigaction(SIGINT, &ctrl_c, NULL) == -1)
		perror("sigaction ctrl + c");
	if (sigaction(SIGQUIT, &ctrl_d, NULL) == -1)
		perror("sigaction ctrl + d");
	if (sigaction(SIGQUIT, &ctrl_backslash, NULL) == -1)
		perror("sigaction ctrl + \\");
}

void	disable_echoctl(void)
{
	struct termios	term;

	if (tcgetattr(STDIN_FILENO, &term) == -1)
	{
		perror("tcgerattr");
		return ;
	}
	term.c_lflag &= ~ECHOCTL;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == -1)
	{
		perror("tcsetattr");
	}
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
}

void	handle_sigbackslash(int signal)
{
	(void)signal;
}
