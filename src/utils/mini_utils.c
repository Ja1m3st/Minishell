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

void	builtin_commands(t_mini *mini, t_token *token)
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
	else if (!ft_strcmp(token->cmd[0], "exit"))
	{
		write(STDOUT_FILENO, "exit\n", 6);
		error(mini, '!');
	}
	else if (!ft_strcmp(token->cmd[0], "setcolour"))
		set_colour(mini, token);
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

void	command_count(t_mini *mini)
{
	t_token *token;
	int	count;

	token = *mini->commands;
	count = 0;
	while (token)
	{
		count++;
		token = token->next;
	}
	mini->cmd_count = count;
	mini->pipes_i = count - 1;
}

t_token	*ft_newtoken(t_token *token)
{
	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->cmd = NULL;
	token->path = NULL;
	token->input_redir = NULL;
	token->output_redir = NULL;
	token->input_file = NULL;
	token->output_file = NULL;
	token->delimeter = NULL;
	token->pipe = NULL;
	token->is_builtin = 0;
	token->complete = 0;
	token->newline = 0;
	token->expansion = 0;
	token->next = NULL;
	return (token);
}

void	ft_tokenadd_back(t_mini *mini, t_token *token)
{
	t_token	*last;

	if (!mini->commands || !token)
		return ;
	if (!*mini->commands)
	{
		*mini->commands = token;
		return ;
	}
	last = *mini->commands;
	while (last->next)
		last = last->next;
	last->next = token;
}
