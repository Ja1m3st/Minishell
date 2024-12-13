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
	mini->og_infile = dup(STDIN_FILENO);
	mini->og_outfile = dup(STDOUT_FILENO);
	mini->fd[0] = -1;
	mini->fd[1] = -1;
	mini->temp_fd = STDIN_FILENO;
}

void	restore_fds(t_mini *mini)
{
	if (dup2(mini->og_infile, STDIN_FILENO) == -1)
		perror("Error restoring stdin");
	if (dup2(mini->og_outfile, STDOUT_FILENO) == -1)
		perror("Error restoring stdout");
}
