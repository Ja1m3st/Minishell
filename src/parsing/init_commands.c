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

void	tokenize(t_mini *mini, char **cmds)
{
	t_token *token;
	int		redir_check;

	if (!cmds || !*cmds)
		return ;
	redir_check = 1;
	while (*cmds)
	{
		if (redir_check)
		{
			token = ft_newtoken(NULL);
			ft_tokenadd_back((t_token **)mini->list, token);
			redir_check = 0;
		}
		if (!ft_strcmp(*cmds, "|"))
		{
			token->type = ft_strdup(*cmds);
			redir_check = 1;
			cmds++;
			continue ;
		}	
		if (is_redirect(*cmds))
		{
			tokenize_redirections(token, cmds);
			if (is_input_redirect(*cmds))
				token->do_swap = 1;
			redir_check = 1;
			continue ;
		}
		if (ft_strcmp(*cmds, "|") && !is_redirect(*cmds))
		{
			tokenize_commands(token, cmds);
		}
        cmds++;
	}
	print_tokens(mini);
}

void	tokenize_redirections(t_token *token, char **cmds)
{
	token->type = ft_strdup(*cmds);
	cmds++;
	if (*cmds)
	{
		token->file = ft_strdup(*cmds);
		cmds++;
	}		
	else
		perror("No file found.\n");
}

void	tokenize_commands(t_token *token, char **cmds)
{
	char	*temp;
	char	*joined;

	token->is_builtin = is_builtin(*cmds);
	temp = ft_strdup(*cmds);
	cmds++;
	while (*cmds && !is_redirect(*cmds) && ft_strcmp(*cmds, "|"))
	{
		joined = ft_strjoin(temp, " ");
		free(temp);
		temp = ft_strjoin(joined, *cmds);
		free(joined);
		cmds++;
	}
	token->cmd = ft_split(temp, ' ');
	if (token->is_builtin == 0)
		token->path = ft_strjoin("/usr/bin/", token->cmd[0]);
	free(temp);
}
