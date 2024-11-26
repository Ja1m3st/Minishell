/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 14:59:33 by ctommasi          #+#    #+#             */
/*   Updated: 2024/11/26 13:14:26 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **duplicate_env(char **env)
{
    int		len;
    char	**new_env;
    int		i;

	i = 0;
	len = array_len(env);
    new_env = malloc((len + 1) * sizeof(char *));
    if (!new_env)
        return NULL;
    while (i < len)
	{
        new_env[i] = ft_strdup(env[i]);
        if (!new_env[i])
		{
            while (i > 0)
                free(new_env[--i]);
            free(new_env);
            return NULL;
        }
		i++;
    }
    new_env[len] = NULL;
    return new_env;
}

void	init_struct(t_mini *mini, char **argv, char **env)
{
	mini->infile = STDIN_FILENO;
	mini->outfile = STDOUT_FILENO;
	mini->env = duplicate_env(env);
	(void)argv;
	mini->env_name = NULL;
	mini->full_name = NULL;
	mini->log_name = NULL;
	mini->path = NULL;
	mini->sesion_name = NULL;
	mini->input = NULL;
	mini->outfile = STDOUT_FILENO;
}
