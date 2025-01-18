/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 16:02:40 by jaimesan          #+#    #+#             */
/*   Updated: 2025/01/16 15:39:34 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_redirections2(t_mini *mini, t_token *token)
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

void	set_redirections(t_mini *mini, t_token *token)
{
	if (token->input_redir && !ft_strcmp(token->input_redir, "<"))
	{
		mini->infile = open(token->input_file, O_RDONLY);
		if (mini->infile == -1)
		{
			write(1, token->input_file, ft_strlen(token->input_file));
			write(1, ": No such file or directory\n", 28);
			g_status = 1;
			exit(g_status);
		}
	}
	else if (token->input_redir && !ft_strcmp(token->input_redir, "<<"))
	{
		here_doc(mini, token);
	}
	set_redirections2(mini, token);
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

void	close_pipes(t_mini *mini, t_token *token, int pipes[][2], int mode)
{
	int		i;

	i = 0;
	if (mode == 1)
	{
		while (i < mini->pipes_i)
		{
			if (i != mini->i - 1 || token->input_redir)
				close(pipes[i][0]);
			if (i != mini->i || token->output_redir)
				close(pipes[i][1]);
			i++;
		}
		if (mini->infile)
			close(mini->infile);
		if (mini->outfile)
			close(mini->outfile);
		return ;
	}
	while (i < mini->pipes_i)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}

