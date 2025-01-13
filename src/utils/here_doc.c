/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctommasi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 13:17:59 by ctommasi          #+#    #+#             */
/*   Updated: 2024/12/17 13:18:00 by ctommasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	here_doc(t_mini *mini, t_token *token)
{
	char	*line;
	int		fd[2];
	t_quote *q = malloc(sizeof(t_quote));

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
		if (line && ft_strchr(line, '$'))
			line = remove_quotes(mini, q, line);
		write(fd[1], line, ft_strlen(line));
		free(line);
	}
	close(fd[1]);
	mini->infile = fd[0];
}
