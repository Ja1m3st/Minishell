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
	free_tree(mini);
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
	if (mini->commands)
		free(mini->commands);
}

void	free_tree(t_mini *mini)
{
	t_token	*token;
	t_token	*next_node;

	if (!mini->commands || !*mini->commands)
		return ;
	token = *mini->commands;
	next_node = NULL;
	while (token)
	{
		next_node = token->next;
		free_tree2(token);
		free(token);
		token = next_node;
	}
	*mini->commands = NULL;
}

void	free_tree2(t_token *token)
{
	if (!token)
		return ;
	if (token->cmd)
		free_arr(token->cmd);
	if (token->path)
		free(token->path);
	if (token->input_redir)
		free(token->input_redir);
	if (token->output_redir)
		free(token->output_redir);
	if (token->input_file)
		free(token->input_file);
	if (token->output_file)
		free(token->output_file);
	if (token->delimeter)
		free(token->delimeter);
	if (token->pipe)
		free(token->pipe);
}
