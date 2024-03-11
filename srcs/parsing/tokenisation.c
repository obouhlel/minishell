/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <obouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 08:54:22 by obouhlel          #+#    #+#             */
/*   Updated: 2024/03/11 11:21:03 by obouhlel         ###   ########.fr       */
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

int	parsing_add(t_parsing **parse, char *str, int token, bool is_in_quote)
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
	new_node->to_join = is_in_quote;
	new_node->next = NULL;
	if (*parse == NULL)
	{
		*parse = new_node;
	}
	else
	{
		current = *parse;
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

void	print_parse(t_parsing *parse)
{
	while (parse)
	{
		printf("%s | %s | %s\n", parse->str, get_type(parse->token), parse->to_join ? "true" : "false");
		parse = parse->next;
	}
}

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
	while (line[(*i) + len] && !is_quote(line[(*i) + len]) && is_token(line[(*i) + len]) == WORD && !is_whitespace(line[(*i) + len]))
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

int	save_token_pipe_or_redir(char *line, int *i, t_parsing **parse)
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
	return (parsing_add(parse, tmp, token, false));
}

int	save_string_and_token(char *line, int *i, t_parsing **parse)
{
	if (line[(*i)] == '\'' || line[(*i)] == '\"')
		return (is_in_quote_token(line, i, line[(*i)], parse));
	else if (is_token(line[(*i)]) != WORD)
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
		if (last->token == WORD && last->to_join && last->prev && last->prev->token == WORD)
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

int	list_copy(t_parsing *parse, t_input **input)
{
	while (parse)
	{
		if (input_add(input, parse->str, parse->token) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		parse = parse->next;
	}
	return (EXIT_SUCCESS);
}

char	*get_token(int token)
{
	if (token == CMD)
		return ("CMD");
	if (token == ARG)
		return ("ARG");
	if (token == PIPE)
		return ("PIPE");
	if (token == REDIR_OUT)
		return ("REDIR_OUT");
	if (token == REDIR_APPEND)
		return ("REDIR_APPEND");
	if (token == REDIR_IN)
		return ("REDIR_IN");
	if (token == HEREDOC)
		return ("HEREDOC");
	if (token == OUTFILE)
		return ("OUTFILE");
	if (token == APPEND)
		return ("APPEND");
	if (token == INFILE)
		return ("INFILE");
	if (token == DELIMETER)
		return ("DELIMETER");
	return ("UNKNOWN");
}

void	set_token(t_input **input)
{
	const char		*token[] = {"|", ">", ">>", "<", "<<", NULL};
	t_input			*current;
	t_input			*previous;
	int				i;

	current = *input;
	while (current)
	{
		i = 0;
		while(token[i])
		{
			if (strcmp(current->str, token[i]) == 0)
			{
				if (current->next && current->next->token == WORD)
				{
					if (current->token == REDIR)
					{
						current->next->token = i + 6;
					}
					else
					{
						current->next->token = CMD;
					}
				}
				current->token = i + 2;
				break ;
			}
			i++;
		}
		if (previous && (previous->token == CMD || previous->token == ARG) && current->token == WORD)
			current->token = ARG;
		if (i == 5 && current->token == WORD)
			current->token = CMD;
		previous = current;
		current = current->next;
	}
}

void	print_input(t_input *input)
{
	while (input)
	{
		printf("%s | %s\n", input->str, get_token(input->token));
		input = input->next;
	}
}

void	set_prev_parsing(t_parsing **parse)
{
	t_parsing	*current;
	t_parsing	*previous;

	current = *parse;
	previous = NULL;
	while (current)
	{
		current->prev = previous;
		previous = current;
		current = current->next;
	}
}

t_input	*tokenisation(char *line)
{
	t_parsing	*parse;
	t_input		*input;

	input = NULL;
	parse = pre_tokenisation(line);
	if (!parse)
		return (NULL);
	printf("\tbefore join\n");
	print_parse(parse);
	set_prev_parsing(&parse);
	if (join_parsing(&parse) == EXIT_FAILURE)
	{
		ft_free_parsing(parse, true);
		return (NULL);
	}
	printf("\tafter join\n");
	print_parse(parse);
	if (list_copy(parse, &input) == EXIT_FAILURE)
	{
		ft_free_parsing(parse, true);
		ft_free_input(input);
		return (NULL);
	}
	ft_free_parsing(parse, false);
	set_token(&input);
	printf("\tafter set token\n");
	print_input(input);
	return (input);
}
