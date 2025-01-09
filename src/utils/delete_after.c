/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_after.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 17:20:28 by ctommasi          #+#    #+#             */
/*   Updated: 2024/12/13 12:29:56 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tree_structure(t_mini *mini)
{
	t_token	*token;
	int		i;
	int		j;

	token = *mini->commands;
	i = 0;
	while (token)
	{
		printf("TOKEN (%d)\n", i);
		if (token->cmd)
		{
			j = 0;
			while (token->cmd[j])
			{
				printf("   cmd[%d]: %s\n", j, token->cmd[j]);
				j++;
			}
		}
		if (token)
			print_tree_structure2(token);
		token = token->next;
		i++;
	}
}

void	print_tree_structure2(t_token *token)
{
	if (token->path)
		printf("   path: %s\n", token->path);
	if (token->input_redir)
		printf("   input_redir: (%s)\n", token->input_redir);
	if (token->input_file)
		printf("   input_file: (%s)\n", token->input_file);
	if (token->output_redir)
		printf("   output_redir: (%s)\n", token->output_redir);
	if (token->output_file)
		printf("   output_file: (%s)\n", token->output_file);
	if (token->delimeter)
		printf("   dlmtr: %s\n", token->delimeter);
	if (token->pipe)
		printf("   pipe: %s\n", token->pipe);
	printf("------------------------------------\n");
}
