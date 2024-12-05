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
	t_token	*token;

	token = NULL;
	if (!cmds || !*cmds)
		return ;
	if (!token || (token && token->complete))
	{
		token = ft_newtoken(NULL);
		ft_tokenadd_back((t_token **)mini->list, token);
	}
	if (*cmds && !is_redirect(*cmds) && ft_strcmp(*cmds, "|"))
	{
		cmds += tokenize_commands(token, cmds);
	}
	if (*cmds && is_redirect(*cmds))
	{
		cmds += tokenize_redirections(token, cmds);
	}
	if (*cmds && !ft_strcmp(*cmds, "|"))
	{
		token->type = ft_strdup(*cmds);
		token->complete = 1;
		cmds++;
	}
	tokenize(mini, cmds);
}

int	tokenize_redirections(t_token *token, char **cmds)
{
	int	i;

	i = 1;
	if (!is_redirect(*cmds))
		return ;
	token->type = ft_strdup(*cmds);
	if (!ft_strcmp(*cmds, ">") || !ft_strcmp(*cmds, ">>"))
	{
		if (++(*cmds))
		{
			token->file = ft_strdup(*cmds);
			i++;
		}
	}
	else if (!ft_strcmp(*cmds, "<<") || !ft_strcmp(*cmds, "<"))
	{
		token->do_swap = 1;
		if (!ft_strcmp(*cmds, "<<"))
		{
			if (++(*cmds))
				token->delimeter = ft_strdup(*cmds);
		}
	}
	token->complete = 1;
	return (i);
}

int	tokenize_commands(t_token *token, char **cmds)
{
	char	*temp;
	char	*joined;
	int		i;

	i = 1;
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
		i++;
	}
	token->cmd = ft_split(temp, ' ');
	if (token->is_builtin == 0)
		token->path = ft_strjoin("/usr/bin/", token->cmd[0]);
	free(temp);
	return (i);
}
