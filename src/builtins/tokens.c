/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 13:10:39 by jaimesan          #+#    #+#             */
/*   Updated: 2024/12/09 14:21:51 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_redir_list(t_redir *head)
{
    t_redir *current = head;

    while (current)
    {
        printf("------ Nodo de redirección ------\n");
        if (current->command)
            printf("Comando: %s\n", current->command);
        else
            printf("Comando: NULL\n");
        if (current->args) {
            printf("Argumentos: ");
            for (int i = 0; current->args[i]; i++) {
                printf("%s ", current->args[i]);
            }
            printf("\n");
        } else {
            printf("Argumentos: NULL\n");
        }
        if (current->input_file)
            printf("Archivo de entrada: %s\n", current->input_file);
        else
            printf("Archivo de entrada: NULL\n");
        if (current->output_file)
            printf("Archivo de salida: %s\n", current->output_file);
        else
            printf("Archivo de salida: NULL\n");
        if (current->heredoc_delim)
            printf("Delimitador heredoc: %s\n", current->heredoc_delim);
        else
            printf("Delimitador heredoc: NULL\n");
        printf("Modo append: %d\n", current->append);
        current = current->next;
        printf("---------------------------------\n");
    }
}

char **ft_append_array(char **array, char *new_elem)
{
    int		i;
	int		j;
    char	**new_array;

	i = 0;
	j = 0;
    if (array)
	{
        while (array[i])
            i++;
    }
    new_array = malloc(sizeof(char *) * (i + 2));
    if (!new_array)
	{
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    while (j < i)
	{
        new_array[j] = ft_strdup(array[j]);
        j++;
    }
    new_array[i] = ft_strdup(new_elem);
    new_array[i + 1] = NULL;
    if (array)
        free_arr(array);
    return (new_array);
}

t_redir *redir(t_mini *mini, int j)
{
    t_redir *block = malloc(sizeof(t_redir));
    char **tokens;
    int i;

    if (!block)
        return (NULL);
    block->command = NULL;
    block->args = malloc(sizeof(char *));
    block->args[0] = NULL;
    block->input_file = NULL;
    block->output_file = NULL;
    block->heredoc_delim = NULL;
    block->append = 0;
    block->next = NULL;
    tokens = ft_split(mini->split_full_cmds[j], ' ');
    if (!tokens)
        return (block);
    i = 0;
    while (tokens[i] && ft_strcmp(tokens[i], "|") != 0)
    {
        if (!ft_strcmp(tokens[i], ">"))
        {
            block->output_file = ft_strdup(tokens[++i]);
            block->append = 0;
        }
        else if (!ft_strcmp(tokens[i], ">>"))
        {
            block->output_file = ft_strdup(tokens[++i]);
            block->append = 1;
        }
        else if (!ft_strcmp(tokens[i], "<"))
            block->input_file = ft_strdup(tokens[++i]);
        else if (!ft_strcmp(tokens[i], "<<"))
            block->heredoc_delim = ft_strdup(tokens[++i]);
        else
            block->args = ft_append_array(block->args, tokens[i]);
        i++;
    }
    if (block->args && block->args[0])
        block->command = block->args[0];
    free_arr(tokens);
    return (block);
}
