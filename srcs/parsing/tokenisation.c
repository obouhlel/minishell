/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <obouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 08:54:22 by obouhlel          #+#    #+#             */
/*   Updated: 2024/03/10 10:25:51 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

int	is_token(char c, char c_next, int *i)
{
	if (c == '|')
		return (PIPES);
	if (c == '<' || c == '>')
	{
		if (c_next == c)
		{
			(*i)++;
			return (DOUBLE_REDIR);
		}
		return (REDIR);
	}
	return (WORD);
}

void	is_in_quote_token(char *line, int *i, char quote, int *nb_token)
{
	(*i)++;
	while (line[*i] && line[*i] != quote)
		(*i)++;
	if (line[*i] == quote)
		(*i)++;
	(*nb_token)++;
}

size_t	count_nb_token(char *line)
{
	int  i;
	int  nb_token;

	i = 0;
	nb_token = 0;
	while (line[i])
	{
		if (is_whitespace(line[i]))
			i++;
		else
		{
			if (line[i] == '\'' || line[i] == '"')
			{
				is_in_quote_token(&line[i], &i, line[i], &nb_token);
				if (line[i] == '\0')
					break ;
			}
			else if (is_token(line[i], line[i + 1], &i))
			{
				nb_token++;
				i++;
			}
			else
			{
				nb_token++;
				while (line[i] && !is_whitespace(line[i]))
					i++;
			}
		}
	}
	return (nb_token);
}

size_t	count_token_size(char *line)
{
	int	size;
	int	i;

	size = 0;
	i = 0;

}

// t_input	*tokenisation(char *line)
// {
// 	size_t	nb_token;
// 	t_input	*input;
// 	size_t	i;
// 	size_t	j;

// 	nb_token = count_nb_token(line);
// 	input = calloc(sizeof(t_input), (nb_token + 1));
// 	if (!input)
// 		return (NULL);
// 	i = 0;
// 	j = 0;
// 	while (line[i])
// 	{
// 		if (is_whitespace(line[i]))
// 			i++;
// 		else
// 		{
// 			if (line[i] == '\'' || line[i] == '"')
// 				is_in_quote_token(&line[i], &i, line[i], &nb_token);
// 			else if (is_token(line[i], line[i + 1], &i))
// 			{
// 				input[j].str = ft_strdup(&line[i]);
// 				input[j].token = is_token(line[i], line[i + 1], &i);
// 				j++;
// 				i++;
// 			}
// 			else
// 			{
// 				input[j].str = ft_strdup(&line[i]);
// 				input[j].token = WORD;
// 				while (line[i] && !is_whitespace(line[i]))
// 					i++;
// 				j++;
// 			}
// 		}
// 	}
// 	return (input);
// }