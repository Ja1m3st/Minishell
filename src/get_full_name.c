/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_full_name.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 16:57:39 by jaimesan          #+#    #+#             */
/*   Updated: 2024/11/25 15:45:00 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void get_name(t_mini *mini)
{
	mini->log_name = getenv("LOGNAME");
}

void    get_sesion_name(t_mini *mini)
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
            if (split3 && split3[0])
                mini->sesion_name = ft_strdup(split3[0]);
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

	get_name(mini);
	get_sesion_name(mini);
    mini->log_name = ft_strjoin(mini->log_name, "@");
	mini->full_name = ft_strjoin(mini->log_name, mini->sesion_name);
}

char	*read_line(t_mini *mini)
{
	char	cwd[1024];
	char	*join1;
	char	*join2;

	if (mini->read_line != NULL)
		free(mini->read_line);
	join1 = ft_strjoin(mini->full_name,":~");
	join2 = ft_strjoin(join1, getcwd(cwd, sizeof(cwd)));
	mini->read_line = ft_strjoin(join2, "$ ");
	free(join1);
	free(join2);
	return (mini->read_line);
}
