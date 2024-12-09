/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 13:30:27 by jaimesan          #+#    #+#             */
/*   Updated: 2024/12/09 14:18:50 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void proces(t_redir *head, t_mini *mini)
{
    t_redir *current;
    pid_t pid;

    current = head;
    pid = fork();
    if (pid == -1)
    {
        perror("Error al hacer fork");
        return;
    }

    if (pid == 0)
    {
		// Queda hacer EOF
		if (current->input_file)
		{
			mini->infile = open(current->input_file, O_RDONLY);
			if (mini->infile == -1) {
				perror("Error al abrir el archivo de entrada");
				exit(EXIT_FAILURE);
			}
			if (dup2(mini->infile, STDIN_FILENO) == -1) {
				perror("Error al redirigir la entrada");
				close(mini->infile);
                exit(EXIT_FAILURE);
			}
			close(mini->infile);
		}
		if (current->output_file)
		{
			if (current->append)
			{
				mini->outfile = open(current->output_file, O_WRONLY | O_APPEND | O_CREAT, 0644);
			}
			else
			{
				mini->outfile = open(current->output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			}
			if (mini->outfile == -1) {
				perror("Error al abrir el archivo de salida");
				return;
			}
			if (dup2(mini->outfile, STDOUT_FILENO) == -1) {
				perror("Error al redirigir la salida");
				close(mini->outfile);
				return;
			}
			close(mini->outfile);
		}
        mini->cmds = head->args;
        get_terminal_commands(mini);
        exit(EXIT_FAILURE);
    }
    else
    {
        waitpid(pid, NULL, 0);
    }
}

void	get_commands(t_mini *mini)
{
	int	i;

	i = 0;
	if (mini->split_full_cmds)
		free_arr(mini->split_full_cmds);
	mini->split_full_cmds = ft_split(mini->full_cmds, '|');
	while (mini->split_full_cmds[i] != NULL)
		i++;
	mini->total_args = i;
//     if (mini->split_full_cmds[0] != NULL)
//     {
//         if (ft_strchr(mini->split_full_cmds[0], '>') || !(ft_strcmp(mini->split_full_cmds[0], ">>"))
//             || ft_strchr(mini->split_full_cmds[0], '<') || !(ft_strcmp(mini->split_full_cmds[0], "<<")))
// 		{
// 			t_redir *block = redir(mini);
// /* 			print_redir_list(block); */
// 			proces(block, mini);
//  		}
//         else
//         {
//             execute_builtins(mini, 0);
//         }
//     }
//     else
//     {
// 	    execute_builtins(mini, 0);
//     }
	execute_builtins(mini, 0);
}

void	execute_builtins(t_mini *mini, int mod)
{
	if (mod == 1)
	{
		cmds(mini, mod);
		exit(EXIT_SUCCESS);
		return ;
	}
	if (mini->total_args == 1)
	{

		if (ft_strchr(mini->split_full_cmds[0], '>') || !(ft_strcmp(mini->split_full_cmds[0], ">>"))
			|| ft_strchr(mini->split_full_cmds[0], '<') || !(ft_strcmp(mini->split_full_cmds[0], "<<")))
		{
			t_redir *block = redir(mini, 0);
			print_redir_list(block);
			proces(block, mini);
		}
		else
		{
			mini->cmds = ft_split(mini->split_full_cmds[0], ' ');
			cmds(mini, mod);
			free_arr(mini->cmds);
		}
	}
	else
	{
		pipex(mini);
	}
}

void	cmds(t_mini *mini, int mod)
{
	if (!ft_strcmp(mini->cmds[0], "history"))
		print_history();
	else if (!ft_strcmp(mini->cmds[0], "env"))
		print_env(mini);
	else if (!ft_strcmp(mini->cmds[0], "echo"))
		echo(mini);
	else if (!ft_strcmp(mini->cmds[0], "pwd"))
		print_pwd(mini);
	else if (!ft_strcmp(mini->cmds[0], "cd"))
		cd(mini);
	else if (!ft_strcmp(mini->cmds[0], "export"))
		export(mini);
	else if (!ft_strcmp(mini->cmds[0], "unset"))
		unset(mini);
	else if (!ft_strncmp(mini->cmds[0], "$", 1))
		printf("%s\n", get_var(mini));
	else if (!ft_strcmp(mini->cmds[0], "exit"))
		error(mini, '!');
	else
	{
		if (mod == 0)
			get_terminal_commands(mini);
	}
}