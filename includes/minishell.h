/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:28:08 by jaimesan          #+#    #+#             */
/*   Updated: 2024/11/25 11:50:10 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

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
}	t_mini;

int		main(int argc, char **argv, char **envp);
void	print_history(void);
void	get_commands(t_mini *mini);
void	echo(t_mini *mini);
void	write_to_fd(t_mini *mini, int fd, int newline);
void	dquote(int fd, int newline);
void	save_cmds(t_mini *mini);
void	print_env(t_mini *mini);
void	get_full_name(t_mini *mini);
void	print_pwd(void);
void	cd(t_mini *mini);

#endif