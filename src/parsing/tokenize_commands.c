/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_commands.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 10:27:59 by ctommasi          #+#    #+#             */
/*   Updated: 2025/01/08 16:53:28 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tokenize_commands(t_mini *mini, char **cmds)
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
		cmds += tokenize_cmds(token, cmds);
/* 	if (*cmds && is_input_redirect(*cmds))
		cmds += tokenize_leftdirections(token, cmds);
	if (*cmds && is_output_redirect(*cmds))
		cmds += tokenize_rightdirections(token, cmds); */
	if (*cmds && !ft_strcmp(*cmds, "|"))
	{
		cmds += tokenize_pipedirections(token, cmds);
		tokenize_commands(mini, cmds);
	}

}

int	tokenize_pipedirections(t_token *token, char **cmds)
{
	token->pipe = ft_strdup(*cmds);
	token->complete = 1;
	return (1);
}

int	tokenize_leftdirections(t_token *token, char **cmds)
{
	token->input_redir = ft_strdup(*cmds);
	if (!ft_strcmp(*cmds, "<<"))
	{
		cmds++;
		if (*cmds)
			token->delimeter = ft_strdup(*cmds);
	}
	else if (!ft_strcmp(*cmds, "<"))
	{
		cmds++;
		if (*cmds)
			token->input_file = ft_strdup(*cmds);
	}
	return (2);
}

int	tokenize_rightdirections(t_token *token, char **cmds)
{
	token->output_redir = ft_strdup(*cmds);
	if (!ft_strcmp(*cmds, ">>") || !ft_strcmp(*cmds, ">"))
	{
		cmds++;
		if (*cmds)
			token->output_file = ft_strdup(*cmds);
	}
	return (2);
}

int	tokenize_cmds(t_token *token, char **cmds)
{
	int		i;

	i = 0;
	token->is_builtin = is_builtin(*cmds);
	while (cmds[i] && ft_strcmp(cmds[i], "|"))
		i++;
	token->cmd = malloc(sizeof(char *) * (i + 1));
	if (!token->cmd)
		return (-1);
	i = 0;
	while (*cmds && ft_strcmp(*cmds, "|"))
	{
        if (*cmds && is_input_redirect(*cmds))
            cmds += tokenize_leftdirections(token, cmds);

        if (*cmds && is_output_redirect(*cmds))
            cmds += tokenize_rightdirections(token, cmds);
        if (**cmds)
        {
            token->cmd[i] = ft_strdup(*cmds);
            i++;
        }
        cmds++;
	}
	token->cmd[i] = NULL;
	if (token->is_builtin == 0)
		token->path = ft_strjoin("/usr/bin/", token->cmd[0]);
	return (i);
}
