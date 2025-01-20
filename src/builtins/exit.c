/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctommasi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 17:30:04 by ctommasi          #+#    #+#             */
/*   Updated: 2025/01/20 17:30:06 by ctommasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_command(t_mini *mini, t_token *token)
{
	int	i;

	i = 0;
	write(STDOUT_FILENO, "exit\n", 6);
	if (token->cmd[1])
	{
		while (token->cmd[1][i])
		{
			if (ft_isalpha(token->cmd[1][i]))
			{
				write(STDOUT_FILENO, "minishell: exit: ", 18);
				write(STDOUT_FILENO, token->cmd[1], ft_strlen(token->cmd[1]));
				write(STDOUT_FILENO, ": numeric argument required\n", 29);
				error(mini, '!');
			}
			i++;
		}
	}
	if (token->cmd[2])
		return ((void)write(STDOUT_FILENO,
				"minishel: exit: too many arguments\n", 36));
	error(mini, '!');
}
