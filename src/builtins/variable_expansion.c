/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctommasi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 13:15:59 by ctommasi          #+#    #+#             */
/*   Updated: 2024/12/16 13:16:01 by ctommasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_variable(t_mini *mini, char *str)
{
	char	*res;
	char	*var_name;
	int		i;
	int		k;

	i = 0;
	k = 0;
	res = ft_strdup("");
	while (str[i])
	{
		if (str[i] == '$')
		{
			i++;
			var_name = extract_var_name(str, &i);
			res = add_var_value(mini, res, var_name);
		}
		else
		{
			res = process_regular_char(res, str[i], &k);
			i++;
		}
	}
	return (res);
}

char	*extract_var_name(char *str, int *i)
{
	char	*var_name;
	int		j;

	var_name = ft_strdup("");
	j = 0;
	while (str[*i] && str[*i] != ' ' && str[*i] != '$' && str[*i] != '\t')
	{
		var_name = ft_realloc(var_name,
				ft_strlen(var_name), ft_strlen(var_name) + 2);
		var_name[j] = str[*i];
		var_name[j + 1] = '\0';
		j++;
		(*i)++;
	}
	return (var_name);
}

char	*add_var_value(t_mini *mini, char *res, char *var_name)
{
	char	*var_value;

	var_value = get_var_value(mini, var_name);
	if (!var_value)
	{
		free(var_name);
		return (res);
	}
	res = ft_strjoin_free(res, var_value);
	free(var_name);
	return (res);
}

char	*process_regular_char(char *res, char current_char, int *k)
{
	res = ft_realloc(res, ft_strlen(res), ft_strlen(res) + 2);
	res[*k] = current_char;
	res[*k + 1] = '\0';
	(*k)++;
	return (res);
}

char	*get_var_value(t_mini *mini, char *var_name)
{
	int		i;
	int		arr_len;
	char	*value;

	arr_len = array_len(mini->env);
	i = 0;
	while (i < arr_len)
	{
		if (ft_strncmp(mini->env[i], var_name, ft_strlen(var_name)) == 0)
		{
			value = ft_strchr(mini->env[i], '=');
			value++;
			return (value);
		}
		i++;
	}
	return (NULL);
}
