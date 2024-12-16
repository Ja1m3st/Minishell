/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctommasi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 19:22:56 by ctommasi          #+#    #+#             */
/*   Updated: 2024/12/13 19:22:57 by ctommasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_fds(t_mini *mini)
{
	mini->infile = STDIN_FILENO;
	mini->outfile = STDOUT_FILENO;
	mini->fd[0] = -1;
	mini->fd[1] = -1;
	mini->is_first_cmd = 1;
	mini->is_last_cmd = 0;
}

void	restore_fds(t_mini *mini)
{
	if (mini->infile != STDIN_FILENO)
	{
		close(mini->infile);
		mini->infile = STDIN_FILENO;
	}
	if (mini->outfile != STDOUT_FILENO)
	{
		close(mini->outfile);
		mini->outfile = STDOUT_FILENO;
	}
}
