/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 11:38:02 by jaimesan          #+#    #+#             */
/*   Updated: 2025/01/10 16:16:00 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int validate_quotes(t_state *state)
{
	if (state->single_quote || state->double_quote)
	{
		free(state->result);
		return (ft_printf("Cierra comillas porfavor :/\n"), 1);
	}
	return (0);
}

static int	handle_single_quote(t_state *state, const char *cmd, size_t *i)
{
	if (cmd[*i] == '\'' && state->double_quote == 0)
	{
		if (state->single_quote == 0 && cmd[*i - 1] == '\\')
			return (0);
		state->single_quote = !state->single_quote;
		return (1);
	}
	return (0);
}

static int	handle_double_quote(t_state *state, char c)
{
	if (c == '\"' && state->single_quote == 0)
	{
		state->double_quote = !state->double_quote;
		return (1);
	}
	return (0);
}

static int handle_escape(t_state *state, const char *cmd, size_t *i, char *result, size_t *j)
{
	if (state->single_quote == 0 && cmd[*i - 1] == '\\' && state->double_quote == 0)
	{
		(*j)--;
		result[*j] = cmd[*i];
		(*i)++;
		(*j)++;
		return (0);
	}
	if (state->double_quote == 1 && cmd[*i] == '\\')
	{
		if (cmd[*i + 1] == '\\' || cmd[*i + 1] == '\"'
			|| cmd[*i + 1] == '`' || cmd[*i + 1] == '\''
			|| cmd[*i + 1] == '$')
		{
			(*i)++;
			result[*j] = cmd[*i];
			(*j)++;
			return (1);
		}
	}
	return (0);
}


static char	*process_cmd(t_state *state, const char *cmd)
{
	char *result;
	size_t i;
	size_t j;

	i = 0;
	j = 0;
	result = malloc(ft_strlen(cmd) + 1);
	if (!result)
		return (NULL);
	while (cmd[i])
	{
		if (handle_single_quote(state, cmd, &i)
			|| handle_double_quote(state, cmd[i])
			|| handle_escape(state, cmd, &i, result, &j))
		{
			i++;
			continue ;
		}
	   	result[j++] = cmd[i++];
	}
	if (validate_quotes(state))
	{
		state->single_quote = 0;
		state->double_quote = 0;
		free(result);
		return (NULL);
	}
	result[j] = '\0';
	return (result);
}

int	check_quotation(t_mini *mini)
{
	t_token	*token;
	char	*processed_cmd;
	int		i;

	token = *(mini->commands);
	while (token)
	{
		i = 0;
		while (token->cmd[i] != NULL)
		{
			processed_cmd = process_cmd(&mini->state, token->cmd[i]);
			if (!processed_cmd)
				return (free_commands(mini), 0);
			free(token->cmd[i]);
			token->cmd[i] = processed_cmd;
			if (ft_strchr(token->cmd[i], '$'))
				token->cmd[i] = expand_variable(mini, token->cmd[i]);
			if (i == 0 && ft_strchr(token->cmd[i], ' ') && !ft_strchr(token->cmd[i], '$'))
				token->cmd = remap_cmds(token);
			if (is_builtin(token->cmd[0]))
				token->is_builtin = 1;
			i++;
		}
		mini->state.double_quote = 0;
		mini->state.single_quote = 0;
		if (!token->is_builtin)
			token->path = ft_strjoin("/usr/bin/", token->cmd[0]);
		if (token->input_file)
		{
			token->input_file = process_cmd(&mini->state, token->input_file);
		}
		if (token->output_file)
			token->output_file = process_cmd(&mini->state, token->output_file);
		token = token->next;
	}
	return (1);
}

