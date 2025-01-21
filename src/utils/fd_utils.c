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

void	set_redirections(t_mini *mini, t_token *token)
{
	if (token->input_redir && !ft_strcmp(token->input_redir, "<"))
	{
		mini->infile = open(token->input_file, O_RDONLY);
		if (mini->infile == -1)
		{
			perror(token->input_file);
			g_status = 1;
			if (!token->access)
				exit(g_status);
			token->access = 0;
		}
	}
	else if (token->input_redir && !ft_strcmp(token->input_redir, "<<"))
	{
		here_doc(mini, token);
	}
	set_redirections2(mini, token);
}

void	set_redirections2(t_mini *mini, t_token *token)
{
	if (token->output_redir && !ft_strcmp(token->output_redir, ">"))
	{
		mini->outfile = open(token->output_file, 01 | 0100 | 01000, 0644);
		if (mini->outfile == -1)
		{
			perror(token->output_file);
			g_status = 1;
			if (!token->access)
				exit(g_status);
			token->access = 0;
		}
	}
	else if (token->output_redir && !ft_strcmp(token->output_redir, ">>"))
	{
		mini->outfile = open(token->output_file,
				O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (mini->outfile == -1)
		{
			perror(token->output_file);
			g_status = 1;
			if (!token->access)
				exit(g_status);
			token->access = 0;
		}
	}
}

void	here_doc(t_mini *mini, t_token *token)
{
	char	*line;
	int		fd[2];

	if (pipe(fd) == -1)
		return (perror("Pipe Error\n"));
	token->delimeter = ft_strdelchar(token->delimeter, "\"\'");
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

void	close_or_free_pipes(t_mini *mini, int mod)
{
	int		i;

	if (mod == 0)
	{
		if (mini->infile && mini->infile > -1)
			close(mini->infile);
		if (mini->infile && mini->outfile > -1)
			close(mini->outfile);
		i = 0;
		while (i < mini->pipes_i && mini->pipes[i] != NULL)
		{
			close(mini->pipes[i][0]);
			close(mini->pipes[i][1]);
			i++;
		}
	}
	else if (mod == 1)
	{
		if (mini->pids)
			free(mini->pids);
		if (mini->pipes)
			ft_freeiarr(mini->pipes, mini->pipes_i);
	}
}

void	single_command(t_mini *mini, t_token *token)
{
	token->access = 1;
	set_redirections(mini, token);
	if (!token->access)
		return ;
	if (mini->infile != -1)
	{
		if (dup2(mini->infile, STDIN_FILENO) == -1)
			return (exit(EXIT_FAILURE), perror("dup2 input error"));
	}
	if (mini->outfile != -1)
	{
		if (dup2(mini->outfile, STDOUT_FILENO) == -1)
			return (exit(EXIT_FAILURE), perror("dup2 output error"));
	}
	builtin_commands(mini, token);
	if (mini->infile != STDIN_FILENO)
		dup2(mini->original_stdin, STDIN_FILENO);
	if (mini->outfile != STDOUT_FILENO)
		dup2(mini->original_stdout, STDOUT_FILENO);
}
