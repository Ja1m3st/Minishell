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
	char	*path;
	char	*type;
	char	*file;
	char	*delimeter;
	char	*pipe;
	int		is_builtin;
	int		do_swap;
	int		complete;
	int		newline;
	int		is_last_cmd;
	struct s_token	*right;
	struct s_token	*left;
} t_token;

typedef struct s_mini
{
	char	*input;
	char	**cmds;
	char	**env;
	char	*log_name;
	char	*sesion_name;
	char	*full_name;
	char	*path;
	char	*env_name;
	char	*oldpath;
	int		newline;
	char	*full_path;
	int		infile;
	int		outfile;
	pid_t	pid;
	t_token	*commands;
	char	**list;
	int	do_swap;
}	t_mini;

//------------------------------------------------------------------MAIN
int		main(int argc, char **argv, char **envp);
void	init_struct(t_mini *mini, char **argv, char **env);
void	handle_sigint(int signal);
void	handle_sigquit(int signal);
void	handle_sigbackslash(int signal);
void	disable_echoctl(void);
void	setup_signals(void);
void	print_history(void);
//------------------------------------------------------------------PIPES
void	pipex(t_mini *mini, t_token *token);
int	swap_fds(t_mini *mini, t_token *token, int temp_fd, int fd[]);
//-------------------------------------------------------------------ENV
void	get_env_name(t_mini *mini);
void	get_session_name(t_mini *mini);
void	print_env(t_mini *mini);
void	dup_env(t_mini *mini, char **env);
char	*join_env_name(t_mini *mini);
//---------------------------------------------------------------COMMANDS
void	builtin_cmds(t_mini *mini, t_token *token);
void	exec_cmds(t_mini *mini);
//-------------------------------------------------------------------ECHO
void	echo(t_token *token);
char	*parse_string(t_token *token);
//--------------------------------------------------------------------PWD
void	print_pwd(t_mini *mini);
//---------------------------------------------------------------------CD
void	cd(t_mini *mini);
//-----------------------------------------------------------------EXPORT
void	export(t_mini *mini);
void	new_export(t_mini *mini);
int		export_exists(t_mini *mini);
int		check_valid_export(t_mini *mini);
//-------------------------------------------------------------------UNSET
void	unset(t_mini *mini);
char	*find_path(t_mini *mini, char *path);
//----------------------------------------------------------VARIABLE CALLS
char	*get_var(t_mini *mini);
char	*find_var(char *str, char c);
//-------------------------------------------------------------------UTILS
void	free_mini(t_mini *mini);
void	free_arr(char **array);
void	error(t_mini *mini, char c);
int		array_len(char **array);
int		is_builtin(char *cmd);
//--------------------------------------------------------------REDIRECTION
void	tokenize(t_mini *mini, char **cmds);
void	ft_tokenadd_back(t_token **lst, t_token *token);
t_token	*ft_newtoken(t_token *token);
int		tokenize_rightdirections(t_token *token, char **cmds);
int		tokenize_leftdirections(t_token *token, char **cmds);
int		tokenize_pipedirections(t_token *token, char **cmds);
int		tokenize_commands(t_token *token, char **cmds);
int		is_redirect(char *cmd);
int		is_input_redirect(char *cmd);
int		is_output_redirect(char *cmd);
int		is_builtins(char *cmd);
void	free_tree(t_mini *mini);
//--------------------------------------------------------------DELETE-AFTER
void	print_tree_structure(t_mini *mini);

#endif
