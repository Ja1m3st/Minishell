/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 17:10:19 by ctommasi          #+#    #+#             */
/*   Updated: 2024/11/26 12:00:52 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export(t_mini *mini)
{
	int		len_i;
	char	**new_env;

	len_i = array_len(mini->env);
	new_env = mini->env;
	new_env[len_i] = malloc(ft_strlen(mini->cmds[1]) * sizeof(char));
	new_env[len_i] = mini->cmds[1];
	new_env[++len_i] = NULL;
	mini->env = new_env;
}
