/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 10:57:13 by jaimesan          #+#    #+#             */
/*   Updated: 2024/12/02 17:41:20 by jaimesan         ###   ########.fr       */
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

static char	*resolve_cd_path(t_mini *mini, char *cwd)
{
	char	*path;

	path = NULL;
	if (!mini->cmds[1] || ft_strchr(mini->cmds[1], '~'))
	{
		if (!mini->cmds[1] || ft_strcmp(mini->cmds[1], "~") == 0)
			return (ft_strdup(find_path(mini, "HOME=")));
		if (ft_strncmp(mini->cmds[1], "~", 1) == 0)
		{
			path = ft_strjoin(find_path(mini, "HOME="), mini->cmds[1] + 1); // lEAK AQUI
			if (!path)
				return (NULL);
		}
	}
	if (!ft_strcmp(mini->cmds[1], "-"))
	{
		if (mini->oldpath == NULL)
			mini->oldpath = ft_strdup(cwd);
		path = ft_strdup(mini->oldpath);
		write(mini->outfile, path, ft_strlen(path));
		write(mini->outfile, "\n", 1);
		if (!path)
			printf("minishell: cd: OLDPWD not set\n");
		return (path);
	}
		path = ft_strdup(mini->cmds[1]);
	return (path);
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
	path = resolve_cd_path(mini, cwd);
	if (!path)
	{
		free(path);
		free(mini->oldpath);
		return ;
	}
	if (chdir(path) == -1)
	{
		free(path);
		free(mini->oldpath);
		perror("Error");
		return ;
	}
	free(path);
	free(mini->oldpath);
	mini->oldpath = NULL;
	mini->oldpath = ft_strdup(cwd);
}
