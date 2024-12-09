/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 15:36:54 by ctommasi          #+#    #+#             */
/*   Updated: 2024/12/03 16:11:34 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error(t_mini *mini, char c)
{
	rl_clear_history();
	free_mini(mini);
	if (c == '!')
		exit(EXIT_SUCCESS);
	exit(EXIT_FAILURE);
}

void	free_mini(t_mini *mini)
{
	if (mini->full_name)
		free(mini->full_name);
	if (mini->log_name)
		free(mini->log_name);
	if (mini->sesion_name)
		free(mini->sesion_name);
	if (mini->env)
		free_arr(mini->env);
	if (mini->oldpath)
		free(mini->oldpath);
	if (mini->full_path)
		free(mini->full_path);
	if (mini->env)
		free(mini->env_name);
	if (mini->path)
		free(mini->path);
	if (mini->input)
		free(mini->input);
}

// void	free_tree(t_mini *mini)
// {
// 	t_token	*cur;
// 	t_token *temp;

// 	temp = *(t_token **)mini->list;
// 	cur = temp;
	
// 	if (!temp)
// 		return ;
// 	while (cur)
// 	{
// 		if (cur->cmd)
// 			free_arr(cur->cmd);
// 		if (cur->path)
// 			free(cur->path);
// 		if (cur->file)
// 			free(cur->file);
// 		if (cur->type)
// 			free(cur->type);
// 		if (cur->delimeter)
// 			free(cur->delimeter);
// 		if (!cur->left)
// 		{
// 			temp = temp->right;
// 			cur = temp;
// 		}
// 		cur = cur->left;
// 	}
// }
