/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:28:08 by jaimesan          #+#    #+#             */
/*   Updated: 2024/12/09 16:43:55 by jaimesan         ###   ########.fr       */
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
# include <termios.h>

typedef struct s_redir {
    char			*command;
    char			**args;
    char			*input_file;
    char			*output_file;
    char			*heredoc_delim;
	int				append;
    struct s_redir	*next;
} t_redir;

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
	t_redir *redir;
}	t_mini;

//-----------------------------------------------------MAIN
int		main(int argc, char **argv, char **envp);
void	init_struct(t_mini *mini, char **argv, char **env);
void	handle_sigint(int signal);
void	handle_sigquit(int signal);
void	handle_sigbackslash(int signal);
void	disable_echoctl(void);
void	setup_signals(void);
//-----------------------------------------------------PIPES
void	pipex(t_mini *mini);
void	execute_command(char *cmd, char **envp);
void	exeve_pipe(int in_fd, int mini_fd[], int i, t_mini *mini);
int		redirect(int in_fd, int mini_fd[], int i, t_mini *mini);
//------------------------------------------------------ENV
void	get_env_name(t_mini *mini);
void	get_session_name(t_mini *mini);
void	print_env(t_mini *mini);
void	dup_env(t_mini *mini, char **env);
char	*join_env_name(t_mini *mini);
//--------------------------------------------------COMMANDS
void	get_commands(t_mini *mini);
void	save_cmds(t_mini *mini);
void	get_terminal_commands(t_mini *mini);
void	execute_builtins(t_mini *mini, int mod);
void	cmds(t_mini *mini, int mod);
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
int		is_builtin(char *cmd);

void	execute_commands_token(char *cmd, char **envp);
int		redirect_token(int in_fd, int mini_fd[], int i, t_mini *mini);
void	execute_commands_token(char *cmd, char **envp);
void	print_redir_list(t_redir *head);
char	**ft_append_array(char **array, char *new_elem);
t_redir *redir(t_mini *mini, int j);
void proces(t_redir *head, t_mini *mini);
void free_redir(t_redir *block);

#endif