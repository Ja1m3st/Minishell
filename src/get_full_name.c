/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_full_name.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 16:57:39 by jaimesan          #+#    #+#             */
/*   Updated: 2024/11/25 15:14:04 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void get_name(t_mini *mini)
{
	mini->log_name = getenv("LOGNAME");
}

void get_sesion_name(t_mini *mini)
{
    int i = 0;
    char **split1 = NULL;
    char **split2 = NULL;
    char **split3 = NULL;

    while (mini->env[i])
	{
        split1 = ft_split(mini->env[i], '=');
        if (!split1 || !split1[0]) {
            free_char_array(split1);
            return;
        }
        if (!ft_strcmp(split1[0], "SESSION_MANAGER"))
		{
            split2 = ft_split(split1[1], '/');
            if (!split2 || !split2[1]) {
                free_char_array(split1);
                free_char_array(split2);
                return;
            }
            split3 = ft_split(split2[1], '.');
            if (split3 && split3[0]) {
                mini->sesion_name = ft_strdup(split3[0]);
            }
            free_char_array(split1);
            free_char_array(split2);
            free_char_array(split3);
            return ;
        }
        free_char_array(split1);
        i++;
    }
}

void	get_full_name(t_mini *mini)
{
	char    *log_name;
	char    *full_name;

	get_name(mini);
	get_sesion_name(mini);
	log_name = ft_strjoin(mini->log_name, "@");
    mini->log_name = log_name;
	full_name = ft_strjoin(mini->log_name, mini->sesion_name);
	mini->full_name = full_name;
}
