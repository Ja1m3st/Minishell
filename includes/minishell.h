/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:28:08 by jaimesan          #+#    #+#             */
/*   Updated: 2024/11/26 16:45:09 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <sys/wait.h>
# include <sys/types.h>

typedef struct s_mini
{
	char	*input;
	char	**cmds;
	char	**env;
	int		infile;
	int		outfile;
	char	*log_name;
	char	*sesion_name;
	char	*full_name;
	char	*path;
	char	*env_name;
	char	*oldpath;
	char	*dquote;
	int		newline;
	char	*full_path;
	pid_t	pid;
}	t_mini;

int		main(int argc, char **argv, char **envp);
void	init_struct(t_mini *mini, char **argv, char **env);
void	dup_env(t_mini *mini, char **env);

void	get_env_name(t_mini *mini);
void	get_session_name(t_mini *mini);
char	*join_env_name(t_mini *mini);

void	print_history(void);
void	get_commands(t_mini *mini);
void	get_terminal_commands(t_mini *mini);

void	print_env(t_mini *mini);

void	echo(t_mini *mini);
void	write_to_fd(t_mini *mini, int fd);
void	dquote(t_mini *mini, int fd);
void	print_to_stdout(t_mini *mini, int temp_fd);
void	dquote_colours(t_mini *mini);

void	print_pwd(void);

void	cd(t_mini *mini);

void	export(t_mini *mini);
void	new_export(t_mini *mini);
int		export_exists(t_mini *mini);
int		check_valid_export(t_mini *mini);

void	unset(t_mini *mini);
char	*find_path(t_mini *mini, char *path);

char	*get_var(t_mini *mini);
char	*find_var(char *str, char c);

void	free_mini(t_mini *mini);
void	free_arr(char **array);
void	error(t_mini *mini, char c);
int		array_len(char **array);

#endif