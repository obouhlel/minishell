/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <obouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 08:54:22 by obouhlel          #+#    #+#             */
/*   Updated: 2024/03/11 15:34:29 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

static
void	set_token_for_current(t_input *current, t_input *previous)
{
	const char		*token[] = {"|", ">", ">>", "<", "<<", NULL};
	int				i;

	i = 0;
	while (token[i])
	{
		if (strcmp(current->str, token[i]) == 0)
		{
			if (current->next && current->next->token == WORD)
			{
				if (current->token == REDIR)
					current->next->token = i + 6;
				else
					current->next->token = CMD;
			}
			current->token = i + 2;
			break ;
		}
		i++;
	}
	if (previous && (previous->token == CMD || previous->token == ARG) \
			&& current->token == WORD)
		current->token = ARG;
	if (i == 5 && current->token == WORD)
		current->token = CMD;
}

static
void	set_token(t_input **input)
{
	t_input			*current;
	t_input			*previous;

	current = *input;
	previous = NULL;
	while (current)
	{
		set_token_for_current(current, previous);
		previous = current;
		current = current->next;
	}
}

static
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

static
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

t_input	*tokenisation(char *line)
{
	t_parsing	*parse;
	t_input		*input;

	input = NULL;
	parse = pre_tokenisation(line);
	if (!parse)
		return (NULL);
	parse->to_join = false;
	set_prev_parsing(&parse);
	if (join_parsing(&parse) == EXIT_FAILURE)
	{
		ft_free_parsing(parse, true);
		return (NULL);
	}
	if (list_copy(parse, &input) == EXIT_FAILURE)
	{
		ft_free_parsing(parse, true);
		ft_free_input(input);
		return (NULL);
	}
	ft_free_parsing(parse, false);
	set_token(&input);
	return (input);
}
