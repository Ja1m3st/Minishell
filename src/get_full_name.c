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

void	get_env_name(t_mini *mini)
{
	mini->log_name = getenv("LOGNAME");
	get_session_name(mini);
	mini->log_name = ft_strjoin(mini->log_name, "@");
	mini->full_name = ft_strjoin(mini->log_name, mini->sesion_name);
}

void	get_session_name(t_mini *mini)
{
	int		i;
	char	**split1;
	char	**split2;
	char	**split3;

	i = 0;
	while (mini->env[i])
	{
		split1 = ft_split(mini->env[i], '=');
		if (!split1 || !split1[0])
			return (free_arr(split1));
		if (!ft_strcmp(split1[0], "SESSION_MANAGER"))
		{
			split2 = ft_split(split1[1], '/');
			if (!split2 || !split2[1])
				return (free_arr(split1), free_arr(split2));
			split3 = ft_split(split2[1], '.');
			if (split3 && split3[0])
				mini->sesion_name = ft_strdup(split3[0]);
			return (free_arr(split1), free_arr(split2), free_arr(split3));
		}
		free_arr(split1);
		i++;
	}
}

char	*join_env_name(t_mini *mini)
{
	char	cwd[1024];
	char	*join1;
	char	*join2;

	if (mini->env_name != NULL)
		free(mini->env_name);
	join1 = ft_strjoin(mini->full_name, ":~");
	join2 = ft_strjoin(join1, getcwd(cwd, sizeof(cwd)));
	mini->env_name = ft_strjoin(join2, "$ ");
	free(join1);
	free(join2);
	return (mini->env_name);
}
