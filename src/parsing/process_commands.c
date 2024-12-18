/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:40:19 by ctommasi          #+#    #+#             */
/*   Updated: 2024/12/17 15:12:42 by jaimesan         ###   ########.fr       */
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
		quote = get_quote(quote, mini->input[i]);
		if (quote != NO_QUOTE || mini->input[i] != ' ')
			cmd = append_character_to_cmd(cmd, mini->input[i], &k);
		if (quote == NO_QUOTE && mini->input[i] == ' ')
			handle_end_of_command(mini->mini_cmds, &cmd, &k, &j);
		i++;
	}
	handle_end_of_command(mini->mini_cmds, &cmd, &k, &j);
	mini->mini_cmds[j] = NULL;
}

void	allocate_command_memory(t_mini *mini)
{
	int	count;

	count = count_commands(mini);
	mini->mini_cmds = malloc(sizeof(char *) * (count + 1));
	if (!mini->mini_cmds)
		return ;
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
	if (*k > 0)
	{
		if (*cmd)
		{
			cmd_list[*j] = ft_strdup(*cmd);
			free(*cmd);
			(*j)++;
		}
		*k = 0;
		*cmd = NULL;
	}
}
