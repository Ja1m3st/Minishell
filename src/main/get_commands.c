/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 13:30:27 by jaimesan          #+#    #+#             */
/*   Updated: 2024/12/02 16:10:26 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_cmds(t_mini *mini)
{
	t_token *cur;

	if (!mini->list)
		return ;
	cur = *(t_token **)mini->list;
	while (cur)
	{
		if (!cur->right)
			cur->is_last_cmd = 1;
		if (!ft_strcmp(cur->type, "<"))
		{
			mini->infile = open("test", O_RDONLY, 0644);
			if (mini->infile == -1)
				perror("Error opening file.\n");
				return ;
		}
		else
			pipex(mini, cur);
		cur = cur->right;
	}
}

void	builtin_cmds(t_mini *mini, t_token *token)
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
		cd(mini);
	else if (!ft_strcmp(token->cmd[0], "export"))
		export(mini);
	else if (!ft_strcmp(token->cmd[0], "unset"))
		unset(mini);
	else if (!ft_strncmp(token->cmd[0], "$", 1))
		printf("%s\n", get_var(mini));
	else if (!ft_strcmp(token->cmd[0], "exit"))
		error(mini, '!');
}

