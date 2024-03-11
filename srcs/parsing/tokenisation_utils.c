/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <obouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 11:44:57 by obouhlel          #+#    #+#             */
/*   Updated: 2024/03/11 12:38:59 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

int	parsing_add(t_parsing **parse, char *str, int token, bool to_join)
{
	t_parsing		*new_node;
	t_parsing		*current;

	if (!str)
		return (EXIT_FAILURE);
	new_node = (t_parsing *)calloc(sizeof(t_parsing), 1);
	if (!new_node)
		return (EXIT_FAILURE);
	new_node->str = str;
	new_node->token = token;
	new_node->to_join = to_join;
	new_node->next = NULL;
	new_node->prev = NULL;
	if (*parse == NULL)
		*parse = new_node;
	else
	{
		current = *parse;
		while (current->next != NULL)
			current = current->next;
		current->next = new_node;
	}
	return (EXIT_SUCCESS);
}

int	input_add(t_input **input, char *str, int token)
{
	t_input		*new_node;
	t_input		*current;

	if (!str)
		return (EXIT_FAILURE);
	new_node = (t_input *)calloc(sizeof(t_input), 1);
	if (!new_node)
		return (EXIT_FAILURE);
	new_node->str = str;
	new_node->token = token;
	new_node->next = NULL;
	if (*input == NULL)
		*input = new_node;
	else
	{
		current = *input;
		while (current->next != NULL)
			current = current->next;
		current->next = new_node;
	}
	return (EXIT_SUCCESS);
}

int	is_type(char c)
{
	if (c == '|')
		return (PIPES);
	if (c == '<' || c == '>')
		return (REDIR);
	return (WORD);
}

int	join_word(t_parsing *parse)
{
	t_parsing	*tmp;
	char		*new_str;

	tmp = parse->next;
	new_str = ft_strjoin(tmp->str, parse->str);
	if (!new_str)
		return (EXIT_FAILURE);
	ft_free((void **)&parse->str);
	parse->str = new_str;
	parse->next = tmp->next;
	ft_free((void **)&tmp->str);
	ft_free((void **)&tmp);
	return (EXIT_SUCCESS);
}

int	join_parsing(t_parsing **parse)
{
	t_parsing	*last;
	t_parsing	*tmp;

	last = *parse;
	while (last->next)
		last = last->next;
	while (last && last->prev)
	{
		if (last->token == WORD && last->to_join && last->prev \
			&& last->prev->token == WORD)
		{
			tmp = last->prev;
			if (join_word(tmp) == EXIT_FAILURE)
				return (EXIT_FAILURE);
			last = *parse;
			while (last != tmp && last->next)
				last = last->next;
		}
		else
			last = last->prev;
	}
	return (EXIT_SUCCESS);
}

char	*redir_string(char *line, int *i, char c, char *redir)
{
	char	*tmp;

	tmp = NULL;
	if (line[*i + 1] == c)
	{
		tmp = ft_strdup(redir);
		(*i) += 1;
	}
	else
		tmp = ft_strdup(redir + 1);
	return (tmp);
}

void ft_free_parsing(t_parsing *parse, bool free_str)
{
	t_parsing *tmp;

	while (parse)
	{
		tmp = parse;
		parse = parse->next;
		if (free_str)
			ft_free((void **)&tmp->str);
		ft_free((void **)&tmp);
	}
}
