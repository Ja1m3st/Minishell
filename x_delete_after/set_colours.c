

		|| !ft_strcmp(cmd, "setcolour")

else if (!ft_strcmp(token->cmd[0], "setcolour"))
		set_colour(mini, token);

static char    *get_colour(char *colour, char *prev_colour)
{
	char	*temp;

	temp = NULL;
	if (!ft_strcmp("black", colour))
		temp = ft_strdup("\033[1;38;5;0m");
	else if (!ft_strcmp("red", colour))
		temp = ft_strdup("\033[1;38;5;1m");
	else if (!ft_strcmp("green", colour))
		temp = ft_strdup("\033[1;38;5;2m");
	else if (!ft_strcmp("yellow", colour))
		temp = ft_strdup("\033[1;38;5;214m");
	else if (!ft_strcmp("blue", colour))
		temp = ft_strdup("\033[1;38;5;4m");
	else if (!ft_strcmp("magenta", colour))
		temp = ft_strdup("\033[1;38;5;5m");
	else if (!ft_strcmp("cyan", colour))
		temp = ft_strdup("\033[1;38;5;6m");
	else if (!ft_strcmp("white", colour))
		temp = ft_strdup("\033[1;38;5;7m");
	else
		return (printf("Did you mean: %s, %s, %s, %s, %s, %s, %s or %s?\n", 
			"black", "red", "green", "yellow", "blue", "magenta", "cyan",
				"white"), prev_colour);
	return (free(prev_colour), temp);
}

void	set_colour(t_mini *mini, t_token *token)
{
	int		i;

	i = 1;
	while (token->cmd[i])
	{
		if (token->cmd[i + 1] && !ft_strcmp("name", token->cmd[i]))
		{
			mini->name_colour = get_colour(token->cmd[i + 1], mini->name_colour);
			i += 2;
		}
		else if (token->cmd[i + 1] && !ft_strcmp("pwd", token->cmd[i]))
		{
			mini->pwd_colour = get_colour(token->cmd[i + 1], mini->name_colour);
			i += 2;
		}
		else
		{
			g_status = 1;
			printf("Correct Usage: setcolour name <colour> pwd <colour>\n");
			return ;
		}
		i++;
	}
}
