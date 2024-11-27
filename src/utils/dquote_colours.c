/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dquote_colours.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctommasi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 11:56:33 by ctommasi          #+#    #+#             */
/*   Updated: 2024/11/27 11:56:35 by ctommasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dquote_colours(t_mini *mini)
{
	char	*join1;
	char	*join2;

	if (mini->dquote != NULL)
		free(mini->dquote);
	join1 = ft_strjoin("\033[1;97m", "dquote > ");
	join2 = ft_strjoin(join1, "\033[0m");
	free(join1);
	mini->dquote = join2;
}
