/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 15:41:12 by ctommasi          #+#    #+#             */
/*   Updated: 2025/01/10 13:47:15 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo(t_mini *mini, t_token *token)
{
	char	*str;

	g_status = 0;
	if (token->cmd[1] && !ft_strcmp(token->cmd[1], "-n"))
		token->newline = 1;
	if (token->newline && !token->cmd[1 + token->newline])
		return ;
	else if (!token->newline && !token->cmd[1])
	{
		write(mini->outfile, "\n", 1);
		return ;
	}
	str = parse_string(token);
	if (str)
	{
		write(mini->outfile, str, ft_strlen(str));
		free(str);
	}
}

char	*parse_string(t_token *token)
{
	int		i;
	char	*echo;
	char	*temp;

	i = 1 + token->newline;
	echo = ft_strdup(token->cmd[i]);
	i++;
	while (token->cmd[i])
	{
		temp = ft_strjoin(echo, " ");
		free(echo);
		echo = ft_strjoin(temp, token->cmd[i]);
		free(temp);
		i++;
	}
	if (token->newline == 0)
	{
		temp = ft_strjoin(echo, "\n");
		free(echo);
		return (temp);
	}
	return (echo);
}
