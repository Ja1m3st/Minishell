/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_commands.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 10:27:59 by ctommasi          #+#    #+#             */
/*   Updated: 2024/12/12 16:00:41 by jaimesan         ###   ########.fr       */
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
		ft_tokenadd_back(mini, token);
	}
	if (*cmds && !is_redirect(*cmds) && ft_strcmp(*cmds, "|"))
		cmds += tokenize_commands(token, cmds, mini);
	if (*cmds && is_input_redirect(*cmds))
		cmds += tokenize_leftdirections(token, cmds, mini);
	if (*cmds && is_output_redirect(*cmds))
		cmds += tokenize_rightdirections(token, cmds, mini);
	if (*cmds && !ft_strcmp(*cmds, "|"))
		cmds += tokenize_pipedirections(token, cmds, mini);
	if (cmds)
		tokenize(mini, cmds);
}

int	tokenize_pipedirections(t_token *token, char **cmds, t_mini *mini)
{
	token->pipe = ft_strdup(*cmds);
	mini->mini_cmds++;
	token->complete = 1;
	return (1);
}

int	tokenize_leftdirections(t_token *token, char **cmds, t_mini *mini)
{
	token->input_redir = ft_strdup(*cmds);
	if (!ft_strcmp(*cmds, "<<"))
	{
		cmds++;
		mini->mini_cmds++;
		if (*cmds)
			token->delimeter = ft_strdup(*cmds);
	}
	else if (!ft_strcmp(*cmds, "<"))
	{
		cmds++;
		mini->mini_cmds++;
		if (*cmds)
			token->input_file = ft_strdup(*cmds);
	}
	return (2);
}

int	tokenize_rightdirections(t_token *token, char **cmds, t_mini *mini)
{
	token->output_redir = ft_strdup(*cmds);
	if (!ft_strcmp(*cmds, ">>") || !ft_strcmp(*cmds, ">"))
	{
		cmds++;
		mini->mini_cmds++;
		if (*cmds)
			token->output_file = ft_strdup(*cmds);
	}
	return (2);
}

int	tokenize_commands(t_token *token, char **cmds, t_mini *mini)
{
	char	*temp;
	char	*joined;
	int		i;

	i = 0;
	token->is_builtin = is_builtin(*cmds);
	while (mini->mini_cmds[i] && ft_strcmp(mini->mini_cmds[i], "|") && !is_redirect(mini->mini_cmds[i]))
		i++;
	token->cmd = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (*cmds && !is_redirect(*cmds) && ft_strcmp(*cmds, "|"))
	{
		token->cmd[i] = ft_strdup(*cmds);
		mini->mini_cmds++;
		cmds++;
		i++;
	}
	token->cmd[i] = NULL;
	if (token->is_builtin == 0)
		token->path = ft_strjoin("/usr/bin/", token->cmd[0]);
	return (i);
}
