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

void	echo(t_mini *mini, t_token *token)
{
	char	*str;

	if (token->cmd[1] && !ft_strncmp(token->cmd[1], "-n", 2))
		token->newline = 1;
	if (!token->cmd[1 + token->newline])
		return ;
	str = parse_string(token);
	write(mini->outfile, str, ft_strlen(str));
	free(str);
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
		i++;
	}
	if (token->newline == 0)
		echo = ft_strjoin(echo, "\n");
	return (echo);
}

