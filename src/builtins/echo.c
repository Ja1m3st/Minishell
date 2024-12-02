/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 15:41:12 by ctommasi          #+#    #+#             */
/*   Updated: 2024/12/02 16:14:26 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo(t_mini *mini)
{
	int	fd;

	fd = open(".echo", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == -1)
		return ;
	if (mini->cmds[1] && !ft_strncmp(mini->cmds[1], "-n", 2))
		mini->newline = 1;
	if (!mini->cmds[1 + mini->newline])
	{
		close(fd);
		return ;
	}
	write_to_fd(mini, fd);
	print_to_stdout(mini, fd);
	close(fd);
	get_next_line(-1);
}

void	write_to_fd(t_mini *mini, int fd)
{
	int	i;
	int	j;
	int	quote;

	quote = 0;
	i = 1 + mini->newline;
	while (mini->cmds[i])
	{
		j = 0;
		while (mini->cmds[i][j])
		{
			if (!ft_strncmp(&mini->cmds[i][j], "\"", 1))
				quote++;
			else
				write(fd, &mini->cmds[i][j], 1);
			j++;
		}
		if (mini->cmds[i + 1])
			write(fd, " ", 1);
		i++;
	}
	if (mini->newline == 0)
		write(fd, "\n", 1);
	if (quote % 2 != 0)
		dquote(mini, fd);
}

void	dquote(t_mini *mini, int fd)
{
	int		i;
	int		stop;
	char	*buf;

	stop = 0;
	if (mini->newline)
		write(fd, "\n", 1);
	while (1)
	{
		write(1, mini->env_name, ft_strlen(mini->env_name));
		write(1, mini->dquote, ft_strlen(mini->dquote));
		buf = get_next_line(0);
		i = 0;
		while (buf[i])
		{
			if (!ft_strncmp(&buf[i++], "\"", 1))
				stop = 1;
		}
		write(fd, buf, ft_strlen(buf) - stop - 1);
		free(buf);
		if (!stop || !mini->newline)
			write(fd, "\n", 1);
		if (stop)
			break ;
	}
}

void	print_to_stdout(t_mini *mini, int temp_fd)
{
	char	*line;

	temp_fd = open(".echo", O_RDONLY);
	if (temp_fd == -1)
		return ;
	while (1)
	{
		line = get_next_line(temp_fd);
		if (!line)
		{
			if (mini->newline)
				write(mini->outfile, "\033[1;38;5;214m%\033[0m\n", 19);
			close(temp_fd);
			break ;
		}
		write(mini->outfile, line, ft_strlen(line));
		free(line);
	}
	get_next_line(-1);
}
