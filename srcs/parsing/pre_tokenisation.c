/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_tokenisation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <obouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 11:39:08 by obouhlel          #+#    #+#             */
/*   Updated: 2024/03/11 12:33:34 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

static
int	is_in_quote_token(char *line, int *i, char quote, t_parsing **parse)
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
	return (parsing_add(parse, tmp, WORD, !have_whitespace_before));
}

static
int	save_word_token(char *line, int *i, t_parsing **parse)
{
	char	*tmp;
	int		len;
	int		j;
	bool	have_whitespace_before;

	have_whitespace_before = false;
	if ((*i) > 0 && line[*i - 1])
		have_whitespace_before = is_whitespace(line[*i - 1]);
	len = 0;
	while (line[(*i) + len] && !is_quote(line[(*i) + len]) && \
		is_type(line[(*i) + len]) == WORD && !is_whitespace(line[(*i) + len]))
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
	return (parsing_add(parse, tmp, WORD, !have_whitespace_before));
}

static
int	save_token_pipe_or_redir(char *line, int *i, t_parsing **parse)
{
	char	*tmp;
	int		token;

	tmp = NULL;
	token = is_type(line[*i]);
	if (token == PIPES)
		tmp = ft_strdup("|");
	else if (token == REDIR)
	{
		if (line[*i] == '<')
			tmp = redir_string(line, i, '<', "<<");
		if (line[*i] == '>')
			tmp = redir_string(line, i, '>', ">>");
	}
	(*i)++;
	return (parsing_add(parse, tmp, token, false));
}

static
int	save_string_and_token(char *line, int *i, t_parsing **parse)
{
	if (is_quote(line[(*i)]))
		return (is_in_quote_token(line, i, line[(*i)], parse));
	else if (is_type(line[(*i)]) != WORD)
		return (save_token_pipe_or_redir(line, i, parse));
	else
		return (save_word_token(line, i, parse));
	return (EXIT_SUCCESS);
}

t_parsing	*pre_tokenisation(char *line)
{
	t_parsing	*parse;
	int			i;

	parse = NULL;
	i = 0;
	while (line[i])
	{
		if (is_whitespace(line[i]))
			i++;
		else
		{
			if (save_string_and_token(line, &i, &parse) == EXIT_FAILURE)
				return (NULL);
		}
	}
	return (parse);
}
