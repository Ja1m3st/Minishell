/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 16:29:04 by ctommasi          #+#    #+#             */
/*   Updated: 2024/12/13 12:54:57 by jaimesan         ###   ########.fr       */
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
		cd(mini);
	else if (!ft_strcmp(token->cmd[0], "export"))
		export(mini, token);
	else if (!ft_strcmp(token->cmd[0], "unset"))
		unset(mini);
	else if (!ft_strncmp(token->cmd[0], "$", 1))
		printf("%s\n", get_var(mini));
	else if (!ft_strcmp(token->cmd[0], "exit"))
		error(mini, '!');
}

int	is_builtin(char *cmd)
{
	return (!ft_strcmp(cmd, "history")
		|| !ft_strcmp(cmd, "env")
		|| !ft_strcmp(cmd, "echo")
		|| !ft_strcmp(cmd, "cd")
		|| !ft_strcmp(cmd, "pwd")
		|| !ft_strcmp(cmd, "export")
		|| !ft_strcmp(cmd, "unset")
		|| !ft_strcmp(cmd, "exit")
		|| !ft_strncmp(cmd, "$", 1));
}

int	is_output_redirect(char *cmd)
{
	return (!ft_strcmp(cmd, ">>") || !ft_strcmp(cmd, ">"));
}

int	is_input_redirect(char *cmd)
{
	return (!ft_strcmp(cmd, "<<") || !ft_strcmp(cmd, "<"));
}

int	is_redirect(char *cmd)
{
	return (is_input_redirect(cmd) || is_output_redirect(cmd));
}
