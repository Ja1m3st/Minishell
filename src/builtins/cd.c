/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 10:57:13 by jaimesan          #+#    #+#             */
/*   Updated: 2024/12/12 15:01:05 by jaimesan         ###   ########.fr       */
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

static char	*check_per(t_mini *mini, char *path)
{
	if (!mini->mini_cmds[1] || ft_strcmp(mini->mini_cmds[1], "~") == 0)
		path = ft_strdup(find_path(mini, "HOME="));
	else if (ft_strncmp(mini->mini_cmds[1], "~", 1) == 0
		&& mini->mini_cmds[1][1] != '\0')
		path = ft_strjoin(find_path(mini, "HOME="), mini->mini_cmds[1] + 1);
	return (path);
}

static char	*resolve_cd_path(t_mini *mini)
{
	char	*path;
	char	*cleaned_cmd;

	path = NULL;
	cleaned_cmd = NULL;
	if (mini->mini_cmds[1])
		cleaned_cmd = ft_strdelchar(mini->mini_cmds[1], "'\"");
	if (mini->mini_cmds[1] && !ft_strncmp(mini->mini_cmds[1], "\"~", 2))
	{
		write(2, "cd: invalid path: \"~\"\n", 22);
		return (free(cleaned_cmd), NULL);
	}
	if (!mini->mini_cmds[1] || ft_strchr(cleaned_cmd, '~'))
		path = check_per(mini, path);
	else if (!ft_strcmp(cleaned_cmd, "-"))
	{
		if (mini->oldpath == NULL)
			return (free(cleaned_cmd), NULL);
		path = ft_strdup(mini->oldpath);
		write(mini->outfile, path, ft_strlen(path));
		write(mini->outfile, "\n", 1);
	}
	else
		path = ft_strdup(cleaned_cmd);
	return (free(cleaned_cmd), path);
}

void	cd(t_mini *mini)
{
	char	*path;
	char	*oldpath;
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)))
		oldpath = ft_strdup(cwd);
	save_oldpath(mini, oldpath);
	if (mini->oldpath == NULL)
		mini->oldpath = ft_strdup(cwd);
	free(oldpath);
	path = resolve_cd_path(mini);
	if (!path)
		return ;
	if (chdir(path) == -1)
	{
		free(path);
		perror("Error");
		return ;
	}
	free(path);
	free(mini->oldpath);
	mini->oldpath = NULL;
	mini->oldpath = ft_strdup(cwd);
}
