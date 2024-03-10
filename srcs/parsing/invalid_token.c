/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invalid_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stle-gof <stle-gof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 08:22:41 by stle-gof          #+#    #+#             */
/*   Updated: 2024/03/10 10:21:06 by stle-gof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

int	is_in_quotes(char *line, size_t *i, char quote)
{
	size_t	j;

	j = *i + 1;
	if (line[j] == '\0')
		return (EXIT_FAILURE);
	while (line[j] && line[j] != quote)
		j++;
	if (!line[j])
		return (EXIT_FAILURE);
	*i = j;
	return (EXIT_SUCCESS);
}

char	check_redirection(char *line, size_t *i, char c, size_t size)
{
	const char	*invalid_token = "|<>";
	size_t		j;

	j = *i;
	if (line[j] != c)
		return ('\0');
	while (line[j] && line[j] == c)
		j++;
	if (j - *i > size)
		return (c);
	if (line[j] == '\0')
		return ('\n');
	if (strchr(invalid_token, line[j]))
		return (line[j]);
	*i = j - 1;
	return ('\0');
}

char	have_invalid_token(char *line)
{
	const char	*invalid_token = ";\\^&*(){}[]_-`~@#%/.,:";

	if (line[0] == '|')
		return ('|');
	return (check_quotes_and_redirections(line, invalid_token));
}

char	check_quotes_and_redirections(char *line, const char *invalid_token)
{
	char	c;
	size_t	i;

	i = 0;
	while (line[i])
	{
		c = line[i];
		if ((c == '\'' || c == '\"') && is_in_quotes(line, &i,
				c) == EXIT_FAILURE)
			return (c);
		c = check_redirection(line, &i, '>', 2);
		if (!c)
			c = check_redirection(line, &i, '<', 2);
		if (!c)
			c = check_redirection(line, &i, '|', 1);
		if (c)
			return (c);
		if (strchr(invalid_token, line[i]))
			return (line[i]);
		i++;
	}
	return ('\0');
}
