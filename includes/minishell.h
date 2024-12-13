/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:28:08 by jaimesan          #+#    #+#             */
/*   Updated: 2024/12/13 12:25:37 by jaimesan         ###   ########.fr       */
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

typedef enum s_quote_type
{
	NO_QUOTE,
	SINGLE_QUOTE,
	DOUBLE_QUOTE
}	t_quote_type;

typedef struct s_token
{
	char			**cmd;
	char			*path;
	char			*input_redir;
	char			*output_redir;
	char			*input_file;
	char			*output_file;
	char			*delimeter;
	char			*pipe;
	struct s_token	*next;
	int				is_builtin;
	int				complete;
	int				newline;
}	t_token;

typedef struct s_mini
{
	char			*input;
	char			**mini_cmds;
	char			**env;
	char			*log_name;
	char			*sesion_name;
	char			*full_name;
	char			*path;
	char			*env_name;
	char			*oldpath;
	char			*full_path;
	int				infile;
	int				outfile;
	int				fd[2];
	int				temp_fd;
	int				is_last_cmd;
	pid_t			pid;
	t_token			**commands;
	t_quote_type	*quote_types;
}	t_mini;

//------------------------------------------------------------------MAIN
int		main(int argc, char **argv, char **envp);
void	init_struct(t_mini *mini, char **argv, char **env);
void	init_fds(t_mini *mini);
//----------------------------------------------------------------SIGNALS
void	handle_sigint(int signal);
void	handle_sigquit(int signal);
void	handle_sigbackslash(int signal);
void	disable_echoctl(void);
void	setup_signals(void);
//----------------------------------------------------------------HISTORY
void	print_history(void);
//--------------------------------------------------------------------ENV
void	get_env_name(t_mini *mini);
void	get_session_name(t_mini *mini);
void	print_env(t_mini *mini);
void	dup_env(t_mini *mini, char **env);
char	*join_env_name(t_mini *mini);
//----------------------------------------------------------------COMMANDS
void	process_commands(t_mini *mini);
void	builtin_commands(t_mini *mini, t_token *token);
void	execute_commands(t_mini *mini);
void	tokenize_commands(t_mini *mini, char **cmds);
void	ft_tokenadd_back(t_mini *mini, t_token *token);
void	set_in_out_file(t_mini *mini, t_token *token);
t_token	*ft_newtoken(t_token *token);
int		tokenize_rightdirections(t_token *token, char **cmds);
int		tokenize_leftdirections(t_token *token, char **cmds);
int		tokenize_pipedirections(t_token *token, char **cmds);
int		tokenize_cmds(t_token *token, char **cmds);
//-------------------------------------------------------------------PIPES
void	pipex(t_mini *mini, t_token *token);
int		swap_fds(t_mini *mini, t_token *token);
//--------------------------------------------------------------------ECHO
void	echo(t_mini *mini, t_token *token);
char	*parse_string(t_token *token);
//---------------------------------------------------------------------PWD
void	print_pwd(t_mini *mini);
//----------------------------------------------------------------------CD
void	cd(t_mini *mini);
//------------------------------------------------------------------EXPORT
void	export(t_mini *mini, t_token *token);
void	new_export(t_mini *mini, t_token *token, int n);
int		check_valid_export(t_token *token, int n);
int		export_exists(t_mini *mini, t_token *token, int n);
//-------------------------------------------------------------------UNSET
void	unset(t_mini *mini);
char	*find_path(t_mini *mini, char *path);
//----------------------------------------------------------VARIABLE CALLS
char	*get_var(t_mini *mini);
char	*find_var(char *str, char c);
//-------------------------------------------------------------------UTILS
void	here_doc(t_mini *mini, t_token *token);
void	input_redirection(t_mini *mini, t_token *token);
void	free_mini(t_mini *mini);
void	free_commands(t_mini *mini);
void	free_commands2(t_token *token);
void	free_arr(char **array);
void	error(t_mini *mini, char c);
int		array_len(char **array);
int		is_builtin(char *cmd);
int		is_redirect(char *cmd);
int		is_input_redirect(char *cmd);
int		is_output_redirect(char *cmd);
void	free_arr_cmds(char **array);
//--------------------------------------------------------------DELETE-AFTER
void	print_tree_structure(t_mini *mini);
void	print_tree_structure2(t_token *token);
void	ft_ptrdelchar(char *str, const char *chars);

#endif
