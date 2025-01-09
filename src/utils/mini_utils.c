/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 13:22:34 by jaimesan          #+#    #+#             */
/*   Updated: 2024/12/13 12:26:47 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_commands(t_mini *mini, t_token *token)
{
	if (!ft_strcmp(token->cmd[0], "history"))
		print_history();
	else if (!ft_strcmp(token->cmd[0], "env"))
		print_env(mini);
	else if (!ft_strcmp(token->cmd[0], "echo"))
		echo(mini, token);
	else if (!ft_strcmp(token->cmd[0], "pwd"))
		print_pwd(mini);
	else if (!ft_strcmp(token->cmd[0], "cd"))
		cd(mini, token);
	else if (!ft_strcmp(token->cmd[0], "export"))
		export(mini, token);
	else if (!ft_strcmp(token->cmd[0], "unset"))
		unset(token, mini);
	else if (!ft_strcmp(token->cmd[0], "exit"))
	{
		write(mini->outfile, "exit\n", 5);
		error(mini, '!');
	}
}

void	free_arr_cmds(char **array)
{
	int	i;

	i = 0;
	if (!array || !*array)
		return ;
	while (array[i])
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	free(array);
	array = NULL;
}

void	free_arr(char **array)
{
	int	i;

	i = 0;
	if (!array || !*array)
		return ;
	while (array[i])
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	free(array);
	array = NULL;
}

int	array_len(char **array)
{
	int	i;

	if (!array || !*array)
		return (-1);
	i = 0;
	while (array && array[i])
		i++;
	return (i);
}

char	*find_path(t_mini *mini, char *path)
{
	int		len;
	int		i;
	char	*find;

	len = array_len(mini->env);
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
