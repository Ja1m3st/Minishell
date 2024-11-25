/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 10:57:13 by jaimesan          #+#    #+#             */
/*   Updated: 2024/11/25 11:29:58 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd(t_mini *mini)
{
	char	*path;

	if (!mini->cmds[1])
	{
		path = getenv("HOME");
		if (!path)
		{
			printf("minishell: cd: HOME not set\n");
			return ;
		}
	}
	else
		path = mini->cmds[1];
	if (chdir(path) == -1)
	{
		perror("minishell: cd");
		return ;
	}
}
