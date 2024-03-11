/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <obouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 11:44:57 by obouhlel          #+#    #+#             */
/*   Updated: 2024/03/11 17:01:59 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

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
	new_str = ft_strjoin(parse->str, tmp->str);
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

void	ft_free_parsing(t_parsing *parse, bool free_str)
{
	t_parsing	*tmp;

	while (parse)
	{
		tmp = parse;
		parse = parse->next;
		if (free_str)
			ft_free((void **)&tmp->str);
		ft_free((void **)&tmp);
	}
}
