/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <obouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 08:54:22 by obouhlel          #+#    #+#             */
/*   Updated: 2024/03/10 14:27:26 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

int	is_token(char c)
{
	if (c == '|')
		return (PIPES);
	if (c == '<' || c == '>')
		return (REDIR);
	return (WORD);
}

int	input_add(t_input **input, char *str, int token, bool is_in_quote)
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
	new_node->to_join = is_in_quote;
	new_node->next = NULL;
	if (*input == NULL)
	{
		*input = new_node;
	}
	else
	{
		current = *input;
		while (current->next != NULL)
		{
			current = current->next;
		}
		current->next = new_node;
	}
	return (EXIT_SUCCESS);
}

char	*get_type(int token)
{
	if (token == WORD)
		return ("WORD");
	if (token == PIPES)
		return ("PIPES");
	if (token == REDIR)
		return ("REDIR");
	return ("UNKNOWN");
}

void	print_input(t_input *input)
{
	while (input)
	{
		printf("%s | %s | %s\n", input->str, get_type(input->token), input->to_join ? "true" : "false");
		input = input->next;
	}
}

int	is_in_quote_token(char *line, int *i, char quote, t_input **input)
{
	int		j;
	int		len;
	char	*tmp;
	bool	have_whitespace_before;

	have_whitespace_before = false;
	if ((*i) > 0 && line[*i - 1])
		have_whitespace_before = is_whitespace(line[*i - 1]);
	(*i)++;
	len = ft_strlen_c(&line[*i], quote);
	tmp = calloc(sizeof(char), (len + 1));
	if (!tmp)
		return (EXIT_FAILURE);
	j = 0;
	while (line[*i] && line[*i] != quote)
	{
		tmp[j] = line[*i];
		(*i)++;
		j++;
	}
	if (line[*i] == quote)
		(*i)++;
	return (input_add(input, tmp, WORD, !have_whitespace_before));
}

int	save_word_token(char *line, int *i, t_input **input)
{
	char	*tmp;
	int		len;
	int		j;
	bool	have_whitespace_before;

	have_whitespace_before = false;
	if ((*i) > 0 && line[*i - 1])
		have_whitespace_before = is_whitespace(line[*i - 1]);
	len = 0;
	while (line[(*i) + len] && !is_quote(line[(*i) + len]) && !is_whitespace(line[(*i) + len]))
		len++;
	tmp = calloc(sizeof(char), (len + 1));
	if (!tmp)
		return (EXIT_FAILURE);
	j = 0;
	while (j < len && line[(*i)])
	{
		tmp[j] = line[(*i)];
		(*i)++;
		j++;
	}
	return (input_add(input, tmp, WORD, !have_whitespace_before));
}

int	save_token_pipe_or_redir(char *line, int *i, t_input **input)
{
	char	*tmp;
	int		token;

	tmp = NULL;
	token = is_token(line[*i]);
	if (token == PIPES)
		tmp = ft_strdup("|");
	else if (token == REDIR)
	{
		if (line[*i] == '<')
		{
			if (line[*i + 1] == '<')
			{
				tmp = ft_strdup("<<");
				(*i) += 1;
			}
			else
				tmp = ft_strdup("<");
		}
		if (line[*i] == '>')
		{
			if (line[*i + 1] == '>')
			{
				tmp = ft_strdup(">>");
				(*i) += 1;
			}
			else
				tmp = ft_strdup(">");
		}
	}
	(*i)++;
	return (input_add(input, tmp, token, false));
}

int	save_string_and_token(char *line, int *i, t_input **input)
{
	if (line[(*i)] == '\'' || line[(*i)] == '\"')
		return (is_in_quote_token(line, i, line[(*i)], input));
	else if (is_token(line[(*i)]) != WORD)
		return (save_token_pipe_or_redir(line, i, input));
	else
		return (save_word_token(line, i, input));
	return (EXIT_SUCCESS);
}

t_input	*tokenisation(char *line)
{
	t_input			*input;
	int				i;

	input = NULL;
	i = 0;
	while (line[i])
	{
		if (is_whitespace(line[i]))
			i++;
		else
		{
			if (save_string_and_token(line, &i, &input) == EXIT_FAILURE)
				return (NULL);
		}
	}
	print_input(input);
	return (input);
}
