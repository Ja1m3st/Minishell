/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 13:22:34 by jaimesan          #+#    #+#             */
/*   Updated: 2025/01/16 15:40:22 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_commands(t_mini *mini, t_token *token, int mod)
{
	if (!ft_strcmp(token->cmd[0], "history"))
		print_history();
	else if (!ft_strcmp(token->cmd[0], "env"))
		print_env(mini);
	else if (!ft_strcmp(token->cmd[0], "echo"))
		echo(token);
	else if (!ft_strcmp(token->cmd[0], "pwd"))
		print_pwd(mini);
	else if (!ft_strcmp(token->cmd[0], "cd"))
		cd(mini, token);
	else if (!ft_strcmp(token->cmd[0], "export"))
		export(mini, token);
	else if (!ft_strcmp(token->cmd[0], "unset"))
		unset(token, mini);
	else if (!ft_strcmp(token->cmd[0], "exit") && mod)
	{
		write(STDOUT_FILENO, "exit\n", 5);
		if (!token->cmd[1])
			error(mini, '!');
	}
	else if (!ft_strcmp(token->cmd[0], "setcolour"))
		set_colour(mini, token);
	return (1);
}

char	*find_path(t_mini *mini, char *path)
{
	int		len;
	int		i;
	char	*find;

	len = ft_arrlen(mini->env);
	i = 0;
	while (i < len)
	{
		if (ft_strncmp(mini->env[i], path, 5) == 0)
		{
			find = ft_strrchr(mini->env[i], '=');
			find++;
			return (find);
		}
		i++;
	}
	return (NULL);
}
