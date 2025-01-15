/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 16:02:40 by jaimesan          #+#    #+#             */
/*   Updated: 2025/01/15 13:50:59 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_in_out_file(t_mini *mini, t_token *token)
{
	if (token->input_redir && !ft_strcmp(token->input_redir, "<"))
	{
		mini->infile = open(token->input_file, O_RDONLY);
		if (mini->infile == -1)
		{
			perror("Error opening file.\n");
			g_status = 2;
			exit(g_status);
		}
	}
	else if (token->input_redir && !ft_strcmp(token->input_redir, "<<"))
	{
		here_doc(mini, token);
	}
	set_in_out_file2(mini, token);
}

void	set_in_out_file2(t_mini *mini, t_token *token)
{
	if (token->output_redir && !ft_strcmp(token->output_redir, ">"))
	{
		mini->outfile = open(token->output_file,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (mini->outfile == -1)
		{
			perror("Error redirecting to file.\n");
			g_status = 2;
			exit(g_status);
		}
	}
	else if (token->output_redir && !ft_strcmp(token->output_redir, ">>"))
	{
		mini->outfile = open(token->output_file,
				O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (mini->outfile == -1)
		{
			perror("Error appending to file.\n");
			g_status = 2;
			exit(g_status);
		}
	}
}

void	init_fds(t_mini *mini)
{
	mini->fd[0] = -1;
	mini->fd[1] = -1;
	mini->outfile = -1;
	mini->infile = -1;
	mini->is_last_cmd = 0;
	mini->prev_fd = STDIN_FILENO;
}

void	close_fds(t_mini *mini)
{
	if (mini->infile != -1)
		close(mini->infile);
	if (mini->outfile != -1)
		close(mini->outfile);
	if (mini->prev_fd != -1 && mini->prev_fd != STDIN_FILENO)
		close(mini->prev_fd);
	if (!mini->is_last_cmd)
	{
		close(mini->fd[0]);
		close(mini->fd[1]);
	}
}

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
		if (line && ft_strchr(line, '$'))
			line = expand_variable(mini, line);
		write(fd[1], line, ft_strlen(line));
		free(line);
	}
	close(fd[1]);
	mini->infile = fd[0];
}
