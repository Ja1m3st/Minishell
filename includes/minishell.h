/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:28:08 by jaimesan          #+#    #+#             */
/*   Updated: 2025/01/15 12:52:55 by jaimesan         ###   ########.fr       */
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

typedef struct s_quote
{
	int	single_quote;
	int	double_quote;
	int	escape;
	int	print;
	int	expansion;
}	t_quote;

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
	int				expansion;
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
	int				prev_fd;
	int				fd[2];
	int				is_last_cmd;
	int				is_first_cmd;
	pid_t			pid;
	t_token			**commands;
	t_quote_type	*quote_types;
}	t_mini;

extern int	g_status;

//------------------------------------------------------------------MAIN
int				main(int argc, char **argv, char **envp);
void			init_struct(t_mini *mini, char **argv, char **env);
void			init_fds(t_mini *mini);
//----------------------------------------------------------------SIGNALS
void			exit_codes(void);
void			handle_sigint(int signal);
void			handle_sigquit(int signal);
void			handle_sigbackslash(int signal);
void			disable_echoctl(void);
void			setup_signals(void);
//----------------------------------------------------------------HISTORY
void			print_history(void);
//--------------------------------------------------------------------ENV
void			get_env_name(t_mini *mini);
void			get_session_name(t_mini *mini);
void			print_env(t_mini *mini);
void			dup_env(t_mini *mini, char **env);
char			*join_env_name(t_mini *mini);
//----------------------------------------------------------------COMMANDS
int				count_commands(t_mini *mini);
void			handle_end_cmd(char **cmd_list, char **cmd, int *k, int *j);
void			handle_redirections(t_mini *mini, char **cmd, int *i, int *j);
char			*append_character_to_cmd(char *cmd, char c, int *k);
void			allocate_command_memory(t_mini *mini);
void			process_commands(t_mini *mini);
void			builtin_commands(t_mini *mini, t_token *token);
void			execute_commands(t_mini *mini);
void			tokenize_commands(t_mini *mini, char **cmds, t_token *cur);
void			ft_tokenadd_back(t_mini *mini, t_token *token);
void			set_in_out_file(t_mini *mini, t_token *token);
void			set_in_out_file2(t_mini *mini, t_token *token);
t_token			*ft_newtoken(t_token *token);
int				tokenize_rightdirections(t_token *token, char **cmds);
int				tokenize_leftdirections(t_token *token, char **cmds);
int				tokenize_cmds(t_token *token, char **cmds);
void			tokenize_utils(t_token *token, char **cmds,
					int *old_len, int *new_len);
void			copy_new_cmds(char **new_cmds, char **cmds,
					int old_len, int new_len);
void			copy_old_cmds(char **new_cmds, t_token *token, int old_len);
char			**allocate_new_cmds(t_token *token, char **cmds,
					int *old_len, int *new_len);
int				get_qouble_single_quotes(t_quote *q, int c);
int				get_escape_quotes(t_quote *q, int c, int c2);
void			get_quotes(t_quote *q, int c, int c2);
//-------------------------------------------------------------------PIPES
void			pipex(t_mini *mini, t_token *token);
void			close_fds(t_mini *mini, t_token *token, int mod);
int				swap_fds(t_mini *mini, t_token *token);
int				swap_fds2(t_mini *mini, t_token *token);
int				execve_commands(t_mini *mini, t_token *token);
//--------------------------------------------------------------------ECHO
void			echo(t_mini *mini, t_token *token);
char			*parse_string(t_token *token);
//---------------------------------------------------------------------PWD
void			print_pwd(t_mini *mini);
//----------------------------------------------------------------------CD
void			cd(t_mini *mini, t_token *token);
char			*check_per(t_mini *mini, t_token *token, char *path);
char			*resolve_cd_path(t_mini *mini, t_token *token);
void			save_oldpath(t_mini *mini, char *oldpath);
char			*resolve_cd_path(t_mini *mini, t_token *token);
//------------------------------------------------------------------EXPORT
void			export(t_mini *mini, t_token *token);
void			new_export(t_mini *mini, t_token *token, int n);
int				check_valid_export(t_token *token, int n);
int				export_exists(t_mini *mini, t_token *token, int n);
//-------------------------------------------------------------------UNSET
void			unset(t_token *token, t_mini *mini);
char			*find_path(t_mini *mini, char *path);
//----------------------------------------------------------VARIABLE CALLS
char			*expand_variable(t_mini *mini, char *str);
char			*extract_var_name(char *str, int *i);
char			*add_var_value(t_mini *mini, char *res, char *var_name);
char			*process_regular_char(char *res, char current_char, int *k);
char			*get_var_value(t_mini *mini, char *var_name);
//----------------------------------------------------------QUOTATIONS
int				check_quotation(t_mini *mini);
char			*remove_quotes(t_mini *mini, t_quote *q, char *cmd);
void			get_quotes(t_quote *q, int c, int c2);
int				get_escape_quotes(t_quote *q, int c, int c2);
int				get_qouble_single_quotes(t_quote *q, int c);
void			init_quotes(t_quote *q);
//-------------------------------------------------------------------UTILS
void			free_main(t_mini *mini);
void			restore_fds(t_mini *mini);
void			here_doc(t_mini *mini, t_token *token);
void			free_mini(t_mini *mini);
void			free_commands(t_mini *mini);
void			free_commands2(t_token *token);
void			error(t_mini *mini, char c);
int				is_builtin(char *cmd);
int				is_redirect(char *cmd);
int				is_input_redirect(char *cmd);
int				is_output_redirect(char *cmd);
int				check_quotation(t_mini *mini);
int				count_commands(t_mini *mini);
t_quote_type	get_quote(t_quote_type quote, char c);
int				is_del(char cmd);
char			**remap_cmds(t_token *token);
void			ft_check_path(t_token *token);
//--------------------------------------------------------------DELETE-AFTER
void			print_tree_structure(t_mini *mini);
void			print_tree_structure2(t_token *token);

#endif