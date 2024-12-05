/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 15:41:12 by ctommasi          #+#    #+#             */
/*   Updated: 2024/12/02 16:14:26 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo(t_mini *mini)
{
	char	*str;

	if (mini->cmds[1] && !ft_strncmp(mini->cmds[1], "-n", 2))
		mini->newline = 1;
	if (!mini->cmds[1 + mini->newline])
		return ;
	str = parse_string(mini);
	write(1, str, ft_strlen(str));
	free(str);
}

char	*parse_string(t_mini *mini)
{
	int		i;
	int		j;
	char	*echo;
	char	mod;

	i = 1 + mini->newline;
	while (mini->cmds[i])
	{
		j = 0;
		if (!ft_strncmp(&mini->cmds[i][j], "\"", 1)
			|| !ft_strncmp(&mini->cmds[i][j], "\'", 1))
			mod = mini->cmds[i][j];
		while (mini->cmds[i][j])
		{
			if (mini->cmds[i][j] != mod)
				echo = ft_strjoin(echo, &mini->cmds[i][j]);
			j++;
		}
		i++;
	}
	if (mini->newline == 0)
		echo = ft_strjoin(echo, "\n");
	return (echo);
}
