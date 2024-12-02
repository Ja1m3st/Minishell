/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:28:08 by jaimesan          #+#    #+#             */
/*   Updated: 2024/12/02 13:20:16 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define _GNU_SOURCE

# include "../libft/includes/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <fcntl.h>
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
	int		total_args;
	char	*full_cmds;
	char	**split_full_cmds;
	pid_t	pid;
}	t_mini;

//-----------------------------------------------------MAIN
int		main(int argc, char **argv, char **envp);
void	init_struct(t_mini *mini, char **argv, char **env);
void	handle_sigint(int signal);
void	handle_sigquit(int signal);
void	setup_signals(void);
//------------------------------------------------------ENV
void	get_env_name(t_mini *mini);
void	get_session_name(t_mini *mini);
void	print_env(t_mini *mini);
void	dup_env(t_mini *mini, char **env);
char	*join_env_name(t_mini *mini);
//--------------------------------------------------COMMANDS
void	get_commands(t_mini *mini);
void	get_terminal_commands(t_mini *mini);
//------------------------------------------------------ECHO
void	echo(t_mini *mini);
void	write_to_fd(t_mini *mini, int fd);
void	dquote(t_mini *mini, int fd);
void	print_to_stdout(t_mini *mini, int temp_fd);
void	dquote_colours(t_mini *mini);
//-------------------------------------------------------PWD
void	print_pwd(t_mini *mini);
//---------------------------------------------------HISTORY
void	print_history(void);
//--------------------------------------------------------CD
void	cd(t_mini *mini);
//----------------------------------------------------EXPORT
void	export(t_mini *mini);
void	new_export(t_mini *mini);
int		export_exists(t_mini *mini);
int		check_valid_export(t_mini *mini);
//------------------------------------------------------UNSET
void	unset(t_mini *mini);
char	*find_path(t_mini *mini, char *path);
//---------------------------------------------VARIABLE CALLS
char	*get_var(t_mini *mini);
char	*find_var(char *str, char c);
//------------------------------------------------------UTILS
void	free_mini(t_mini *mini);
void	free_arr(char **array);
void	error(t_mini *mini, char c);
int		array_len(char **array);
void	pipex(t_mini *mini);
int		check_tub(t_mini *mini);
void	save_cmds(t_mini *mini);
void	execute_command(char *cmd, char **envp);
void	built_int(int in_fd, int mini_fd[], int i, t_mini *mini);
void	execute_command(char *cmd, char **envp);
void	exeve_pipe(int in_fd, int mini_fd[], int i, t_mini *mini);
int		ft_redirects(int in_fd, int mini_fd[], int i, t_mini *mini);

#endif