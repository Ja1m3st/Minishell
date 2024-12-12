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
int	check_valid_var(char **cmds);
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
		cmds += tokenize_commands(token, cmds);
	if (*cmds && is_input_redirect(*cmds))
		cmds += tokenize_leftdirections(token, cmds);
	if (*cmds && is_output_redirect(*cmds))
		cmds += tokenize_rightdirections(token, cmds);
	if (*cmds && !ft_strcmp(*cmds, "|"))
		cmds += tokenize_pipedirections(token, cmds);
	if (cmds)
		tokenize(mini, cmds);
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

int	tokenize_commands(t_token *token, char **cmds)
{
	char	*temp;
	char	*joined;
	int		i;

	i = 1;
	token->is_builtin = is_builtin(*cmds);
	temp = ft_strdelchar(*cmds, "\"");
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
	joined = ft_strdelchar(temp, "\"");
	token->cmd = ft_split(joined, ' ');
	if (token->is_builtin == 0)
		token->path = ft_strjoin("/usr/bin/", token->cmd[0]);
	free(temp);
	free(joined);
	return (i);
}
