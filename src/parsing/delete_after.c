/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_after.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctommasi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 17:20:28 by ctommasi          #+#    #+#             */
/*   Updated: 2024/12/05 17:20:43 by ctommasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	print_tree_structure(t_token *node, int depth, char side)
{
	if (!node)
		return;
	for (int i = 0; i < depth; i++)
		printf("    ");

	if (side == 'L')
		printf("L---- ");
	else if (side == 'R')
		printf("R---- ");
	printf("%s", node->cmd[0]);
	if (node->cmd[1])
		printf(" %s", node->cmd[1]);
	if (node->type)
		printf(" (%s)", node->type);
	printf("\n");
	print_tree_structure(node->left, depth + 1, 'L');
	print_tree_structure(node->right, depth + 1, 'R');
}

void	print_tokens_tree(t_mini *mini)
{
	if (!mini || !mini->list)
		return;

	t_token *root = *(t_token **)mini->list;
	print_tree_structure(root, 0, ' ');
}
