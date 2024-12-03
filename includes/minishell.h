/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:28:08 by jaimesan          #+#    #+#             */
/*   Updated: 2024/12/02 15:13:06 by jaimesan         ###   ########.fr       */
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

typedef struct s_token
{
	char	**cmd;
	char	*mods;
	char	*path;
	int	is_builtin;
	int	redir_count;
	char	*type;
	char	*file;
	struct s_token *next;
	
}		t_token;

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
	int	d_quote;
	int	s_quote;
	t_token *commands;
	char	**list;
}	t_mini;

//-----------------------------------------------------MAIN
int		main(int argc, char **argv, char **envp);
void	init_struct(t_mini *mini, char **argv, char **env);
void	handle_sigint(int signal);
void	handle_sigquit(int signal);
void	handle_sigbackslash(int signal);
void	disable_echoctl(void);
void	setup_signals(void);
void	print_history(void);
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
void	get_terminal_commands(t_mini *mini);
void	execute_builtins(t_mini *mini, int mod);
void	cmds(t_mini *mini, int mod);
//------------------------------------------------------ECHO
void	echo(t_mini *mini);
void	write_to_fd(t_mini *mini);
char	*parse_string(t_mini *mini);
//-------------------------------------------------------PWD
void	print_pwd(t_mini *mini);
//-----------------------*cmdsd);
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
//------------------------------------------------------REDIRECTION
void	init_commands(t_mini *mini, char **cmds);
void	ft_tokenadd_back(t_token **lst, t_token *new);
t_token	*ft_newtoken(t_token *new);
int	is_redirect(char *cmd);
int	is_builtins(char *cmd);
void print_tokens(t_mini *mini);
void	redirect_parsing(t_mini *mini, t_token *new_token, char **cmds);
void	builtin_parsing(t_mini *mini, t_token *new_token, char **cmds);
void	shell_cmd_parsing(t_mini *mini, t_token *new_token, char **cmds);

#endif
