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
	g_status = 0;
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

char	**remap_cmds(t_token *token)
{
	char	**new_cmd;
	char	*path;

	new_cmd = ft_split(token->cmd[0], ' ');
	if (!new_cmd)
		return (token->cmd);
	path = ft_strjoin("/usr/bin/", new_cmd[0]);
	if (!is_builtin(new_cmd[0]) && access(path, F_OK))
		return (ft_freearr(new_cmd), free(path), token->cmd);
	return (ft_freearr(token->cmd), free(path), new_cmd);
}
