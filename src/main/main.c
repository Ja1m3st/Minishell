/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:43:39 by jaimesan          #+#    #+#             */
/*   Updated: 2024/12/13 17:27:14 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int process_input_multi(char *str, char chr)
{
    int i = 0;
    int j = 0;

	if (str[i] == chr)
	{
		i++;
		while (str[i] != '\0')
		{
			if (str[i] == '\\')
			{	
				if (str[i + 1] == '\"')
				{
					str[j++] ='\"';
					i+=2;
				}
				else if (str[i + 1] == '\'')
				{
					str[j++] ='\'';
					i+=2;
				}
				else if (str[i + 1] == 'n')
				{
					str[j++] ='\\';
					str[j++] ='n';
					i+=2;
				}
				else if (str[i + 1] == 't')
				{
					str[j++] ='\\';
					str[j++] ='t';
					i+=2;
				}
				if (str[i + 1] == '\\')
				{
					str[j++] ='\\';
					i+=2;
				}
				else if (str[i+ 1] != '\0')
					str[j++] = str[i++];
				else
				{
					i++;
					break ;
				}
			}
			else
				str[j++] = str[i++];
		}
		if (str[i - 1] == chr)
            j--;
		str[j] = '\0';
		return (1);
	}
	return (0);
}

int process_input_single(char *str, char chr)
{
    int i = 0;
    int j = 0;

	if (str[i] == chr)
	{
		i++;
		while (str[i] != '\0')
		{
			if (str[i] == '\\')
			{	
				if (str[i + 1] == '\"')
				{
					str[j++] ='\\';
					str[j++] ='\"';
					i+=2;
				}
				else if (str[i + 1] == '\'')
				{
					str[j++] ='\\';
					str[j++] ='\'';
					i+=2;
				}
				else if (str[i + 1] == 'n')
				{
					str[j++] ='\\';
					str[j++] ='n';
					i+=2;
				}
				if (str[i + 1] == '\\')
				{
					str[j++] ='\\';
					i++;
				}
				else if (str[i+ 1] != '\0')
					str[j++] = str[i++];
				else
				{
					i++;
					break ;
				}
			}
			else
				str[j++] = str[i++];
		}
		if (str[i - 1] == chr)
            j--;
		str[j] = '\0';
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	t_mini	mini;
	int		i;
	char	*env_name;

	if (argc != 1)
		return (1);
	init_struct(&mini, argv, env);
	while (1)
	{
		i = 0;
		env_name = join_env_name(&mini);
		mini.input = readline(env_name);
		if (!mini.input)
			break ;
		if (*mini.input)
			add_history(mini.input);
		process_commands(&mini);
		while (mini.mini_cmds[i] && !ft_strchr(mini.mini_cmds[i], '~'))
		{
			if (mini.mini_cmds[i][0] == '"')
				process_input_multi(mini.mini_cmds[i++], '"');
			else
				process_input_single(mini.mini_cmds[i++], '\'');
		}
		tokenize_commands(&mini, mini.mini_cmds);
		print_tree_structure(&mini);
		execute_commands(&mini);
		free_arr_cmds(mini.mini_cmds);
		mini.mini_cmds = NULL;
		free_commands(&mini);
		free(mini.input);
	}
	error(&mini, '!');
	return (0);
}
