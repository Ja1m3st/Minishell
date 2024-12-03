/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctommasi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 10:27:59 by ctommasi          #+#    #+#             */
/*   Updated: 2024/12/03 10:28:00 by ctommasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_commands(t_mini *mini, char **cmds)
{
	t_token *new_token;

	if (!cmds || !*cmds)
		return ;
	new_token = ft_newtoken(NULL);
	if (is_redirect(*cmds))
	{
		redirect_parsing(mini, new_token, cmds);
	
	}
	else if (is_builtins(*cmds))
	{
		builtin_parsing(mini, new_token, cmds);
	}
	else
	{
		shell_cmd_parsing(mini, new_token, cmds);
	}
	ft_tokenadd_back((t_token **)mini->list, new_token);
	if (*cmds && is_redirect(new_token->type))
		cmds++;
	if (*cmds)
		init_commands(mini, cmds + 1);
	return (print_tokens(mini));
}

void	redirect_parsing(t_mini *mini, t_token *new_token, char **cmds)
{
	new_token->type = ft_strdup(*cmds);
	cmds++;
	if (*cmds)
			new_token->file = ft_strdup(*cmds);
	else
		perror("No file found.\n");
}

void	builtin_parsing(t_mini *mini, t_token *new_token, char **cmds)
{
	char	*temp;
	char	*joined;

	new_token->is_builtin = 1;
	temp = ft_strdup(*cmds);
	cmds++;
	while (*cmds && !is_redirect(*cmds))
	{
		joined = ft_strjoin(temp, " ");
		free(temp);
		temp = ft_strjoin(joined, *cmds);
		free(joined);
		cmds++;
	}
	new_token->cmd = ft_split(temp, ' ');
	// free(temp);
}


void	shell_cmd_parsing(t_mini *mini, t_token *new_token, char **cmds)
{
	char	*temp;
	char	*joined;

	new_token->is_builtin = 0;
	temp = ft_strdup(*cmds);
	cmds++;
	while (*cmds && !is_redirect(*cmds))
	{
		joined = ft_strjoin(temp, " ");
		free(temp);
		temp = ft_strjoin(joined, *cmds);
		free(joined);
		cmds++;
	}
	new_token->cmd = ft_split(temp, ' ');
	new_token->path = ft_strjoin("/usr/bin/", new_token->cmd[0]);
	// free(temp);
}



