/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 15:41:12 by ctommasi          #+#    #+#             */
/*   Updated: 2025/01/16 16:18:42 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo(t_token *token)
{
	char	*str;
	int	n;

	g_status = 0;
	n = 0;
	token->newline = 0;
	if (token->cmd[1] && !ft_strncmp(token->cmd[1], "-n", 2))
	{
		token->newline = 1;
		if (token->cmd[1][2] && !ft_strncmp(token->cmd[1], "-n ", 3))
			n = 1;
	}
	if (token->newline && !token->cmd[1 + token->newline] && !n)
		return ;
	else if (!token->newline && !token->cmd[1])
	{
		write(STDOUT_FILENO, "\n", 1);
		return ;
	}
	str = parse_string(token, n);
	if (str)
	{
		write(STDOUT_FILENO, str, ft_strlen(str));
		free(str);
	}
}

char	*parse_string(t_token *token, int n)
{
	int		i;
	char	*echo;
	char	*temp;

	i = 1 + token->newline - n;
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
