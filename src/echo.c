/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctommasi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 15:41:12 by ctommasi          #+#    #+#             */
/*   Updated: 2024/11/22 15:41:13 by ctommasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo(t_mini *mini)
{
	int	i;
	int	j;
	int	fd;
	int	newline;
	int	quote;

	newline = 0;
	quote = 0;
	fd = open(".echo", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == -1)
		return ;
	if (!ft_strncmp(mini->cmds[1], "-n", 2))
		newline = 1;
	// if (!ft_strncmp(&mini->cmds[2][0], "\"", 1))
	// 	quote +;
	i = 1 + newline;
	while (mini->cmds[i])
	{
		j = 0;
		while (mini->cmds[i][j])
		{
			write(fd, &mini->cmds[i][j], 1);
			// if (!ft_strncmp(&mini->cmds[i][j], "\"", 1))
			// 	quote++;
			j++;
		}
		printf("quote = %d\n", quote);
		write(fd, " ", 1);
		i++;
	}
	if (!newline)
		write(fd, "\n", 1);
	// if (quote % 2 == 0)
	// 	dquote(fd);
	close(fd);
}

void	dquote(int fd)
{
	char	*buf;
	int	i;
	int	stop;

	stop = 0;
	while (1)
	{
		buf = get_next_line(0);
		i = 0;
		while (buf[i])
		{
			if (!ft_strcmp(&buf[i], "\""))
				stop = 1;
			i++;
		}
		write(fd, buf, ft_strlen(buf));
		free(buf);
		if (stop)
			break ;
	}
	get_next_line(-1);
}
