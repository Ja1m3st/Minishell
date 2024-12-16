/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 16:02:40 by jaimesan          #+#    #+#             */
/*   Updated: 2024/12/13 13:33:25 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipex(t_mini *mini, t_token *token)
{
	mini->pid = fork();
	if (mini->pid == -1)
		return (perror("Fork error\n"));
	if (mini->pid == 0)
	{
		if (token->input_redir || token->output_redir)
			set_in_out_file(mini, token);
		swap_fds(mini, token);
	}
	close(mini->fd[1]);
	mini->outfile = mini->fd[0];
	waitpid(mini->pid, NULL, 0);
}

int	swap_fds(t_mini *mini, t_token *token)
{
	if (token->input_redir)
	{
		if (dup2(mini->infile, STDIN_FILENO) == -1)
			return (perror("dup2 error (input)"), exit(EXIT_FAILURE), 1);
	}
	else if (!mini->is_first_cmd)
		if (dup2(mini->fd[0], STDIN_FILENO) == -1)
			return (perror("dup2 error (pipe input)"), exit(EXIT_FAILURE), 1);
	if (token->output_redir)
	{
		if (dup2(mini->outfile, STDOUT_FILENO) == -1)
			return (perror("dup2 error (output)"), exit(EXIT_FAILURE), 1);
	}
	else if (!mini->is_last_cmd)
		if (dup2(mini->fd[1], STDOUT_FILENO) == -1)
			return (perror("dup2 error (pipe output)"), exit(EXIT_FAILURE), 1);
	close(mini->fd[0]);
	close(mini->fd[1]);
	if (token->is_builtin)
		return (builtin_commands(mini, token), exit(EXIT_SUCCESS), 0);
	else if (execve(token->path, token->cmd, mini->env) == -1)
		return (perror("Failed to execute command"), exit(EXIT_FAILURE), 1);
	return (0);
}
