/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 15:53:03 by jaimesan          #+#    #+#             */
/*   Updated: 2024/11/29 15:18:09 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_pwd(t_mini *mini)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)))
	{
		write(mini->outfile, cwd, ft_strlen(cwd));
		write(mini->outfile, "\n", 1);
		g_status = 0;
	}
	else
		g_status = 1;
}
