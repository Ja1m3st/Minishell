/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_commands_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:51:06 by jaimesan          #+#    #+#             */
/*   Updated: 2025/01/14 14:53:50 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char	**allocate_new_cmds(t_token *token, char **cmds,
// 	int *old_len, int *new_len)
// {
// 	tokenize_utils(token, cmds, old_len, new_len);
// 	return (malloc(sizeof(char *) * (*old_len + *new_len + 1)));
// }

// void	copy_old_cmds(char **new_cmds, t_token *token, int old_len)
// {
// 	int	i;

// 	i = 0;
// 	while (i < old_len)
// 	{
// 		new_cmds[i] = ft_strdup(token->cmd[i]);
// 		i++;
// 	}
// }

// void	copy_new_cmds(char **new_cmds, char **cmds, int old_len, int new_len)
// {
// 	int	j;

// 	j = 0;
// 	while (j < new_len)
// 	{
// 		new_cmds[j + old_len] = ft_strdup(cmds[j]);
// 		j++;
// 	}
// 	new_cmds[old_len + new_len] = NULL;
// }
