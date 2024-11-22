/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 13:30:27 by jaimesan          #+#    #+#             */
/*   Updated: 2024/11/22 13:30:29 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	get_commands(t_mini *mini)
{
	if (!ft_strcmp(mini->input, "history"))
		print_history(mini);
}
