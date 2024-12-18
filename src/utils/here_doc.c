/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 13:17:59 by ctommasi          #+#    #+#             */
/*   Updated: 2024/12/18 15:53:19 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	here_doc(t_mini *mini, t_token *token)
{
	char	*line;
	int		fd[2];

	if (pipe(fd) == -1)
		return (perror("Pipe Error\n"));
	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(0);
		if (!line)
			break ;
		if (!ft_strncmp(line, token->delimeter, ft_strlen(token->delimeter))
			&& line[ft_strlen(token->delimeter)] == '\n')
		{
			free(line);
			break ;
		}
		line = expand_var_to_value(mini, line);
		write(fd[1], line, ft_strlen(line));
		free(line);
	}
	close(fd[1]);
	if (dup2(fd[0], mini->infile) == -1)
		return (perror("Here Doc Error.\n"), exit(EXIT_FAILURE));
	close(fd[0]);
}

char	*expand_var_to_value(t_mini *mini, char *line)
{
	char	*temp;

	if (ft_strchr(line, '$'))
	{
		temp = expand_variable(mini, line);
		free(line);
		line = ft_strdup(temp);
		free(temp);
	}
	return (line);
}
