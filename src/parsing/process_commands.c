/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:40:19 by ctommasi          #+#    #+#             */
/*   Updated: 2025/01/09 12:56:33 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_commands(t_mini *mini)
{
	int				i;
	int				j;
	int				k;
	t_quote_type	quote;
	char			*cmd;

	i = 0;
	j = 0;
	k = 0;
	cmd = NULL;
	quote = NO_QUOTE;
	allocate_command_memory(mini);
	while (mini->input[i])
	{
        if (mini->input[i] == '\\' && mini->input[i + 1] != '\0')
        {
            // Agregar el carácter siguiente literal
			cmd = append_character_to_cmd(cmd, mini->input[i], &k);
            cmd = append_character_to_cmd(cmd, mini->input[i + 1], &k);
            i += 2; // Saltar el carácter escapado
            continue;
        }
		quote = get_quote(quote, mini->input[i]);
		if (quote != NO_QUOTE || (mini->input[i] != ' ' && !is_delimeter(mini->input[i])))
			cmd = append_character_to_cmd(cmd, mini->input[i], &k);
		if (quote == NO_QUOTE && (mini->input[i] == ' ' || is_delimeter(mini->input[i])))
			handle_end_of_command(mini->mini_cmds, &cmd, &k, &j);
		if (quote == NO_QUOTE && is_delimeter(mini->input[i]))
			handle_redirections(mini, &cmd, &i, &j);
		i++;
	}
	handle_end_of_command(mini->mini_cmds, &cmd, &k, &j);
	mini->mini_cmds[j] = NULL;
}

void	allocate_command_memory(t_mini *mini)
{
	int	count;
	int	i;

	count = count_commands(mini);
	mini->mini_cmds = malloc(sizeof(char *) * (count + 1));
	if (!mini->mini_cmds)
	{
		perror("Memory Allocation Failure\n");
		exit(EXIT_FAILURE);
		return ;
	}
	i = 0;
	while (i < count)
	{
		mini->mini_cmds[i] = NULL;
		i++;
	}
}

void	handle_redirections(t_mini *mini, char **cmd, int *i, int *j)
{
	*cmd = ft_realloc(*cmd, 0, 2);
	(*cmd)[0] = mini->input[*i];
	(*cmd)[1] = '\0';
	if (mini->input[*i + 1] && is_delimeter(mini->input[*i + 1]))
	{
		(*i)++;
		*cmd = ft_realloc(*cmd, 1, 3);
		(*cmd)[1] = mini->input[*i];
		(*cmd)[2] = '\0';
	}
	mini->mini_cmds[*j] = ft_strdup(*cmd);
	free(*cmd);
	*cmd = NULL;
	(*j)++;
}

char	*append_character_to_cmd(char *cmd, char c, int *k)
{
	cmd = ft_realloc(cmd, *k, *k + 2);
	cmd[*k] = c;
	(*k)++;
	cmd[*k] = '\0';
	return (cmd);
}

void	handle_end_of_command(char **cmd_list, char **cmd, int *k, int *j)
{
	if (*k > 0 && *cmd)
	{
		cmd_list[*j] = ft_strdup(*cmd);
		free(*cmd);
		(*j)++;
		*k = 0;
		*cmd = NULL;
	}
}
