/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:28:08 by jaimesan          #+#    #+#             */
/*   Updated: 2025/01/16 15:41:25 by jaimesan         ###   ########.fr       */
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
	t_token			**commands;
	t_quote_type	*quote_types;
	t_quote_type	q;
	char		*name_clr;
	char		*pwd_clr;
	int				infile;
	int				outfile;
	int			cmd_count;
	int			pipes_i;
	int			i;
}	t_mini;

extern int	g_status;
//------------------------------------------------------------------MAIN
int				main(int argc, char **argv, char **envp);
int				main_commands(t_mini *mini);
void			init_struct(t_mini *mini, char **argv, char **env);
//----------------------------------------------------------------SIGNALS
void			exit_codes(void);
void			handle_sigint(int signal);
void			handle_sigquit(int signal);
void			disable_echoctl(void);
void			setup_signals(void);
//--------------------------------------------------------------------ENV
void			get_env_name(t_mini *mini);
void			get_session_name(t_mini *mini);
void			dup_env(t_mini *mini, char **env);
char			*join_env_name(t_mini *mini);
//--------------------------------------------------------------------BUILTINS
void			echo(t_token *token);
void			print_pwd(t_mini *mini);
void			cd(t_mini *mini, t_token *token);
void			export(t_mini *mini, t_token *token);
void			unset(t_token *token, t_mini *mini);
void			print_history(void);
void			set_colour(t_mini *m, t_token *t);
char			*expand_variable(t_mini *mini, char *str);
void			print_env(t_mini *mini);
//----------------------------------------------------------------COMMANDS
void			process_commands(t_mini *mini);
int				tokenize_commands(t_mini *mini, char **cmds, t_token *cur);
void			execute_commands(t_mini *mini);
void			set_redirections(t_mini *mini, t_token *token);
void			close_pipes(t_mini *mini, t_token *token,
							int pipes[][2], int mode);
int				count_commands(t_mini *mini);
void			command_count(t_mini *mini);
int				count_commands(t_mini *mini);
void			builtin_commands(t_mini *mini, t_token *token);
void			ft_tokenadd_back(t_mini *mini, t_token *token);
t_token			*ft_newtoken(t_token *token);
void			get_quotes(t_quote *q, int c, int c2);
void			here_doc(t_mini *mini, t_token *token);
//----------------------------------------------------------------QUOTATIONS
int				check_quotation(t_mini *mini);
void			init_quotes(t_quote *q);
//-------------------------------------------------------------------UTILS
void			free_main(t_mini *mini);
void			free_mini(t_mini *mini);
void			free_commands(t_mini *mini);
void			free_commands2(t_token *token);
void			error(t_mini *mini, char c);
int				is_builtin(char *cmd);
int				is_redirect(char *cmd);
int				is_input_redirect(char *cmd);
int				is_output_redirect(char *cmd);
int				count_commands(t_mini *mini);
t_quote_type	get_quote(t_quote_type quote, char c);
int				is_del(char cmd);
void			ft_check_path(t_token *token);
char			*find_path(t_mini *mini, char *path);
char			*resolve_cd_path(t_mini *mini, t_token *token);
char			*check_per(t_mini *mini, t_token *token, char *path);
int				check_valid_var(char *var_name);
//--------------------------------------------------------------DELETE-AFTER
void			print_tree_structure(t_mini *mini);
void			print_tree_structure2(t_token *token);


#endif
