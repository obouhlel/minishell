/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxe_error_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <obouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 16:50:04 by obouhlel          #+#    #+#             */
/*   Updated: 2024/03/11 16:59:25 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "minishell.h"

char	*remove_whitespace(char *line)
{
	size_t	i;
	size_t	j;
	char	*new_line;

	new_line = ft_strdup(line);
	if (!new_line)
		return (NULL);
	bzero(new_line, ft_strlen(line));
	i = 0;
	j = 0;
	while (line[i])
	{
		if (is_whitespace(line[i]))
		{
			i++;
			continue ;
		}
		new_line[j] = line[i];
		i++;
		j++;
	}
	return (new_line);
}

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

char	*syntaxe_redir(char *line, size_t i, char redir)
{
	size_t	j;

	j = 0;
	while (line[j + i] == redir)
		j++;
	if (line[i + j] == '\0')
		return (ft_strdup("newline"));
	if (j > 3 && redir == '>')
		return (ft_strdup(">>"));
	else if (j > 3 && redir == '<')
		return (ft_strdup("<<"));
	else if (j == 3 && redir == '>')
		return (ft_strdup(">"));
	else if (j == 3 && redir == '<')
		return (ft_strdup("<"));
	return ("");
}

char	*invalid_token(char *line, size_t i)
{
	const char	*invalid_token = ";&(){}[]";
	size_t		j;

	j = 0;
	while (invalid_token[j])
	{
		if (line[i] == invalid_token[j])
			return (ft_substr(line, i, 1));
		j++;
	}
	return ("");
}

bool	error_syntaxe_pipe(char *line, size_t i)
{
	size_t	j;

	j = 0;
	while (line[j + i] && line[j + i] == '|')
		j++;
	if (j > 2)
		return (true);
	if (line[i + j] == '\0')
		return (true);
	if (line[i + j] == '<' || line[i + j] == '>')
	{
		while (line[j + i] && (line[j + i] == '<' || line[j + i] == '>'))
			j++;
		if (line[i + j] == '\0')
			return (true);
	}
	return (false);
}
