/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 13:41:38 by jaimesan          #+#    #+#             */
/*   Updated: 2025/01/14 13:44:26 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*resolve_cd_path(t_mini *mini, t_token *token)
{
	char	*path;
	char	*cleaned_cmd;

	path = NULL;
	cleaned_cmd = NULL;
	if (token->cmd[1])
		cleaned_cmd = ft_strdelchar(token->cmd[1], "'\"");
	if (token->cmd[1] && (!ft_strncmp(token->cmd[1], "\"~", 2)
			|| !ft_strncmp(token->cmd[1], "\'~", 2)))
		return (handle_tilde_error(cleaned_cmd));
	if (token->cmd[1] && !ft_strcmp(cleaned_cmd, "-"))
		return (handle_dash_option(mini, cleaned_cmd));
	path = handle_general_path(mini, token, cleaned_cmd);
	free(cleaned_cmd);
	return (path);
}

char	*handle_general_path(t_mini *mini, t_token *token, char *cleaned_cmd)
{
	if (!token->cmd[1] || ft_strchr(cleaned_cmd, '~')
		|| !ft_strcmp(cleaned_cmd, "--"))
		return (check_per(mini, token, NULL));
	return (ft_strdup(cleaned_cmd));
}

char	*handle_dash_option(t_mini *mini, char *cleaned_cmd)
{
	char	*path;

	if (mini->oldpath == NULL)
	{
		free(cleaned_cmd);
		return (NULL);
	}
	path = ft_strdup(mini->oldpath);
	write(mini->outfile, path, ft_strlen(path));
	write(mini->outfile, "\n", 1);
	free(cleaned_cmd);
	return (path);
}

char	*handle_tilde_error(char *cleaned_cmd)
{
	write(2, "cd: ~: No such file or directory\n", 34);
	free(cleaned_cmd);
	return (NULL);
}
