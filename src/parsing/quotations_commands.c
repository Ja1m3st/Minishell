#include "minishell.h"

int	get_qouble_single_quotes(t_quote *q, int c)
{
	if (c == '\"' && !q->SINGLE_QUOTES)
	{
		if (!q->ESCAPE)
		{
			q->DOUBLE_QUOTES = !q->DOUBLE_QUOTES;
			q->PRINT = 0;
		}
		else
			q->PRINT = 1;
		q->ESCAPE = 0;
		return (0);
	}
	if (c == '\'' && !q->DOUBLE_QUOTES)
	{
		if (!q->ESCAPE)
		{
			q->SINGLE_QUOTES = !q->SINGLE_QUOTES;
			q->PRINT = 0;
		}
		else
			q->PRINT = 1;
		q->ESCAPE = 0;
		return (0);
	}
	return (1);
}

int	get_escape_quotes(t_quote *q, int c, int c2)
{
	if (c == '\\')
	{
		if (q->ESCAPE)
		{
			q->PRINT = 1;
			q->ESCAPE = 0;
		}
		else if (q->DOUBLE_QUOTES && (c2 == '\"' || c2 == '$' || c2 == '\\'))
		{
			q->PRINT = 0;
			q->ESCAPE = 1;
		}
		else if (!q->DOUBLE_QUOTES && !q->SINGLE_QUOTES)
		{
			q->PRINT = 0;
			q->ESCAPE = 1;
		}
		else
		{
			q->PRINT = 1;
			q->ESCAPE = 0;
		}
		return (0);
	}
	return (1);
}

void	get_quotes(t_quote *q, int c, int c2)
{
	if (!get_qouble_single_quotes(q, c))
		return ;
	if (!get_escape_quotes(q, c, c2))
		return ;
	if (c == '$' && !q->SINGLE_QUOTES && !q->ESCAPE)
	{
		q->EXPANSION = 1;
		q->PRINT = 0;
		return ;
	}
	if (q->ESCAPE)
	{
		q->ESCAPE = 0;
		q->PRINT = 1;
		return ;
	}
	q->PRINT = 1;
}

char	*remove_quotes(t_mini *mini, t_quote *q, char *cmd)
{
	char	*res;
	char	*temp;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	res = ft_strdup("");
	init_quotes(q);
	while (cmd[i])
	{
		get_quotes(q, cmd[i], cmd[i + 1]);
		j = ft_strlen(res);
		if (q->PRINT)
		{
			res = ft_realloc(res, j, j + 2);
			res[j++] = cmd[i];
			res[j] = '\0';
		}
		if (q->EXPANSION)
		{
			temp = ft_strdup("$");
			i++;
			k = 1;
			while (cmd[i] && (ft_isalnum(cmd[i]) || cmd[i] == '_' || cmd[i] == '?'))
			{
				temp = ft_realloc(temp, k, k + 2);
				temp[k++] = cmd[i];
				temp[k] = '\0';
				if (cmd[i - 1] && cmd[i - 1] == '?' && ft_isascii(cmd[i]))
					break ;
				i++;
			}
			q->EXPANSION = 0;
			temp = expand_variable(mini, temp);
			res = ft_strjoinf(res, temp);
			free(temp);
			continue ;
		}
		i++;
	}
	return (free(cmd), res);
}

int	check_quotation(t_mini *mini)
{
	t_token	*token;
	t_quote *q;
	int		i;

	q = malloc(sizeof(t_quote));
	token = *(mini->commands);
	while (token)
	{
		i = 0;
		while (token->cmd[i] != NULL)
		{
			token->cmd[i] = remove_quotes(mini, q, token->cmd[i]);
			if (q->SINGLE_QUOTES || q->DOUBLE_QUOTES)
				return (write(2, "Error: Unclosed quotes\n", 23), free(q), 0);
			if (is_builtin(token->cmd[0]))
				token->is_builtin = 1;
			if (!ft_strncmp(token->cmd[i], "./", 2))
				token->path = ft_strjoin(getenv("$HOME"), token->cmd[0]);
			i++;
		}
		if (!token->is_builtin && !token->path)
			token->path = ft_strjoin("/usr/bin/", token->cmd[0]);
		if (token->input_file)
			token->input_file = remove_quotes(mini, q, token->output_file);
		if (token->output_file)
			token->output_file = remove_quotes(mini, q, token->output_file);
		token = token->next;
	}
	return (1);
}
