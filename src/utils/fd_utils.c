/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctommasi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 19:22:56 by ctommasi          #+#    #+#             */
/*   Updated: 2024/12/13 19:22:57 by ctommasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_fds(t_mini *mini)
{
	mini->infile = STDIN_FILENO;
	mini->outfile = STDOUT_FILENO;
	mini->fd[0] = -1;
	mini->fd[1] = -1;
	mini->is_first_cmd = 1;
	mini->is_last_cmd = 0;
}

void	restore_fds(t_mini *mini)
{
	if (mini->infile != STDIN_FILENO)
	{
		close(mini->infile);
		mini->infile = STDIN_FILENO;
	}
	if (mini->outfile != STDOUT_FILENO)
	{
		close(mini->outfile);
		mini->outfile = STDOUT_FILENO;
	}
}

char	**remap_cmds(t_token *token)
{
	char	**new_cmd;
	int	i;
	int	len;

	new_cmd = malloc(3 * sizeof(char *));
	if (!new_cmd)
		return (token->cmd);
	new_cmd[0] = malloc(ft_strchrlen(token->cmd[0], ' '));
	if (!new_cmd[0])
		return (free_arr(new_cmd), token->cmd);
	ft_strlcpy(new_cmd[0], token->cmd[0], ft_strchrlen(token->cmd[0], ' ') + 1);
	new_cmd[1] = malloc(ft_strlen(token->cmd[0]) - ft_strlen(new_cmd[0]));
	if (!new_cmd[1])
		return (free_arr(new_cmd), free(new_cmd[0]), token->cmd);
	len = ft_strlen(new_cmd[0]) + 1;
	i = 0;
	while (token->cmd[0][len])
		new_cmd[1][i++] = token->cmd[0][len++];
	new_cmd[1][i] = '\0';
	new_cmd[2] = NULL;
	token->path = ft_strjoin("/usr/bin/", new_cmd[0]);
	if (!is_builtin(new_cmd[0]) || access(token->path, F_OK))
		return (free_arr(new_cmd), token->cmd);
	return (free_arr(token->cmd), new_cmd);
}
