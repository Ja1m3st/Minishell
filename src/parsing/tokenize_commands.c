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
		if (mini->do_swap)
			ft_tokenadd_left((t_token **)mini->list, token);
		else
			ft_tokenadd_right((t_token **)mini->list, token);
		mini->do_swap = 0;
	}
	if (*cmds && !is_redirect(*cmds) && ft_strcmp(*cmds, "|"))
		cmds += tokenize_commands(token, cmds);
	if (*cmds && is_output_redirect(*cmds))
		cmds += tokenize_rightdirections(token, cmds, mini);
	if (*cmds && is_input_redirect(*cmds))
		cmds += tokenize_leftdirections(token, cmds, mini);
	if (*cmds && !ft_strcmp(*cmds, "|"))
		cmds += tokenize_pipedirections(token, cmds, mini);
	tokenize(mini, cmds);
}

int	tokenize_pipedirections(t_token *token, char **cmds, t_mini *mini)
{
	token->type = ft_strdup(*cmds);
	token->complete = 1;
	mini->do_swap = 0;
	return (1);
}

int	tokenize_leftdirections(t_token *token, char **cmds, t_mini *mini)
{
	token->type = ft_strdup(*cmds);
	mini->do_swap = 1;
	if (!ft_strcmp(*cmds, "<<"))
	{
		cmds++;
		if (*cmds)
			token->delimeter = ft_strdup(*cmds);
	}
	token->complete = 1;
	return (1);
}

int	tokenize_rightdirections(t_token *token, char **cmds, t_mini *mini)
{
	int	i;

	i = 1;
	token->type = ft_strdup(*cmds);
	mini->do_swap = 0;
	cmds++;
	if (*cmds)
	{
		token->file = ft_strdup(*cmds);
		i++;
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
