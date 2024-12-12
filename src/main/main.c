/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:43:39 by jaimesan          #+#    #+#             */
/*   Updated: 2024/12/12 16:36:36 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void process_command(t_mini *mini)
{
    int     i;
    int     j;
    int     len; 
    t_quote_type current_quote;
    char    *current_cmd;
    int     current_cmd_len;
    char    ch; 

    len = ft_strlen(mini->input);
    mini->quote_types = malloc(sizeof(char*) * len);
    mini->mini_cmds = malloc(sizeof(char*) * len); // Para almacenar los comandos procesados
    current_cmd = malloc(len + 1);
    current_quote = NO_QUOTE;
    current_cmd_len = 0;
    i = 0;
    j = 0;
    while (i < len)
    {
        ch = mini->input[i];
        // Detectar apertura de comillas
        if (ch == '\'')
        {
            if (current_quote == NO_QUOTE)
                current_quote = SINGLE_QUOTE;
            else if (current_quote == SINGLE_QUOTE)
                current_quote = NO_QUOTE;
        }
        else if (ch == '\"')
        {
            if (current_quote == NO_QUOTE)
                current_quote = DOUBLE_QUOTE;
            else if (current_quote == DOUBLE_QUOTE)
                current_quote = NO_QUOTE;
        }

        // Si estamos dentro de comillas, almacenamos el carácter
        if (current_quote != NO_QUOTE || ch != ' ')
            current_cmd[current_cmd_len++] = ch;

        // Cuando encontramos un espacio fuera de las comillas, es un separador de argumento
        if (ch == ' ' && current_quote == NO_QUOTE && current_cmd_len > 0)
        {
            current_cmd[current_cmd_len] = '\0';
            mini->mini_cmds[j++] = ft_strdup(current_cmd);
            current_cmd_len = 0;
        }
        i++;
    }
    // Añadir el último comando si es necesario
    if (current_cmd_len > 0)
    {
        current_cmd[current_cmd_len] = '\0';
        mini->mini_cmds[j] = ft_strdup(current_cmd);
        j++;
    }
    mini->mini_cmds[j] = NULL;
    free(current_cmd);
}

void	ft_ptrdelchar(char *str, const char *chars)
{
	int		i;
	int		j;

	if (!str || !chars)
		return;
	i = 0;
	j = 0;
	while (str[i])
	{
		if (!ft_strchr(chars, str[i]))
			str[j++] = str[i];
		i++;
	}
	str[j] = '\0';
}

int	main(int argc, char **argv, char **env)
{
	t_mini	mini;
	char	*env_name;
    int     i;

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
		process_command(&mini);
       	while (mini.mini_cmds[i])
            ft_ptrdelchar(mini.mini_cmds[i++], "\'\"");
		tokenize(&mini, mini.mini_cmds);
		// print_tree_structure(&mini);
		exec_cmds(&mini);
        free_tree(&mini);
        free(mini.input);
        free_arr(mini.mini_cmds);
	}
	error(&mini, '!');
	return (0);
}
