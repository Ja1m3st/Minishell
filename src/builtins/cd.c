/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 10:57:13 by jaimesan          #+#    #+#             */
/*   Updated: 2024/11/26 16:42:56 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	save_oldpath(t_mini *mini, char *oldpath)
{
	char	**new_env;
	int		len;
	int		i;
	int		j;
	int		oldpath_len;

	len = array_len(mini->env);
	oldpath_len = ft_strlen(oldpath);
	new_env = malloc((len + 1) * sizeof(char *));
	if (!new_env)
		error(mini, 'M');
	i = 0;
	j = 0;
	while (i < len)
	{
		if (ft_strncmp(mini->env[i], "OLDPWD=", 6 + 1) == 0)
			new_env[j++] = ft_strjoin("OLDPWD=", oldpath);
		else
			new_env[j++] = ft_strdup(mini->env[i]);
		i++;
	}
	new_env[j] = NULL;
	free_arr(mini->env);
	mini->env = new_env;
}

void	cd(t_mini *mini)
{
	char	*path;
	char	*oldpath;
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)))
		oldpath = ft_strdup(cwd);
	save_oldpath(mini, oldpath);
	free(oldpath);
	if (!mini->cmds[1])
	{
		if (!find_path(mini, "HOME="))
			return ;
		path = ft_strdup(find_path(mini, "HOME="));
		if (!path)
		{
			printf("minishell: cd: HOME not set\n");
			return ;
		}
	}
	else if (!ft_strcmp(mini->cmds[1], "-"))
	{
		path = ft_strdup(mini->oldpath);
		ft_printf("%s\n", path);
		if (!path)
		{
			printf("minishell: cd: OLDPWD not set\n");
			return ;
		}
	}
	else
	{
		path = ft_strdup(mini->cmds[1]);
	}
	if (chdir(path) == -1)
	{
		perror("Error");
		return ;
	}
	free(path);
	free(mini->oldpath);
	mini->oldpath = NULL;
	mini->oldpath = ft_strdup(cwd);
}
