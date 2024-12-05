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

void	print_tokens(t_mini *mini)
{
	t_token	*current;
	int		i;

	current = *(t_token **)mini->list;
	i = 0;
	while (current)
	{
		printf("Token %d.- :\n", i);
		if (current->cmd)
		{
			for (int i = 0; current->cmd[i]; i++)
			printf("  cmd[%d]: %s\n", i, current->cmd[i]);
		}
		if (current->complete)
			printf("  complete: %d\n", current->complete);
		if (current->do_swap)
			printf("  do_swap???: %d\n", current->do_swap);
		if (current->is_builtin)
			printf("  is_builtin: %d\n", current->is_builtin);
		if (current->path)
			printf("  path: %s\n", current->path);
		if (current->type)
			printf("  type: %s\n", current->type);
		if (current->file)
			printf("  file: %s\n", current->file);
		printf("----------------------\n");
		current = current->next;
		i++;
	}
}
