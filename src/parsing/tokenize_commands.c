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

void	tokenize_commands(t_mini *mini, char **cmds, t_token *cur)
{
	t_token	*token;

	token = cur;
	if (!cmds || !*cmds)
		return ;
	if (!token || (token && token->complete))
	{
		token = ft_newtoken(NULL);
		ft_tokenadd_back(mini, token);
	}
	if (*cmds && !is_redirect(*cmds) && ft_strcmp(*cmds, "|"))
		cmds += tokenize_cmds(token, cmds);
	if (*cmds && is_input_redirect(*cmds))
		cmds += tokenize_leftdirections(token, cmds);
	if (*cmds && is_output_redirect(*cmds))
		cmds += tokenize_rightdirections(token, cmds);
	if (*cmds && !ft_strcmp(*cmds, "|"))
	{
		token->pipe = ft_strdup(*cmds);
		token->complete = 1;
		cmds++;
		tokenize_commands(mini, cmds, NULL);
		return ;
	}
	tokenize_commands(mini, cmds, token);
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

void	tokenize_utils(t_token *token, char **cmds, int *old_len, int *new_len)
{
	while (token->cmd && token->cmd[*old_len])
		(*old_len)++;
	while (cmds[*new_len] && ft_strcmp(cmds[*new_len], "|")
		&& !is_redirect(cmds[*new_len]))
		(*new_len)++;
}

int	tokenize_cmds(t_token *token, char **cmds)
{
	int		new_len;
	int		old_len;
	int		i;
	int		j;
	char	**new_cmds;

	old_len = 0;
	new_len = 0;
	tokenize_utils(token, cmds, &old_len, &new_len);
	new_cmds = malloc(sizeof(char *) * (old_len + new_len + 1));
	if (!new_cmds)
		return (-1);
	i = 0;
	while (i < old_len)
	{
		new_cmds[i] = ft_strdup(token->cmd[i]);
		i++;
	}
	j = 0;
	while (j < new_len)
	{
		new_cmds[j + old_len] = ft_strdup(cmds[j]);
		j++;
	}
	new_cmds[old_len + new_len] = NULL;
	if (token->cmd)
		free_arr(token->cmd);
	token->cmd = new_cmds;
	return (j);
}
