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


void	print_tree_structure(t_mini *mini)
{
	t_token	*cur;
	int	i;

	cur = *(t_token **)mini->list;
	i = 0;
	while (cur)
	{
		printf("TOKEN [%d]\n", i);
		if (cur->cmd)
		{
			for (int i = 0; cur->cmd[i]; i++)
				printf("   cmd[%d]: %s\n", i, cur->cmd[i]);
		}
		if (!cur->is_builtin)
			printf("   path: %s\n", cur->path);
		if (cur->type)
			printf("   type: (%s)\n", cur->type);
		if (cur->file)
			printf("   file: %s\n", cur->file);
		if (cur->delimeter)
			printf("   dlmtr: %s\n", cur->delimeter);
		if (cur->pipe)
			printf("   pipe: %s\n", cur->pipe);
		printf("\n");
		cur = cur->right;
		i++;
	}
}

