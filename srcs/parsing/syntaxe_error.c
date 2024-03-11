/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxe_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <obouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 10:30:10 by obouhlel          #+#    #+#             */
/*   Updated: 2024/03/11 16:55:02 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

static
char	*check_token(char *line)
{
	char		*tmp;
	size_t		i;

	i = 0;
	while (line[i])
	{
		if (is_quote(line[i]) && is_in_quotes(line, &i, line[i]))
			return (ft_strdup("newline"));
		else if (line[i] == '|' && error_syntaxe_pipe(line, i))
			return (ft_strdup("|"));
		else if (line[i] == '>' || line[i] == '<')
		{
			tmp = syntaxe_redir(line, i, line[i]);
			if (!tmp || tmp[0] != '\0')
				return (tmp);
		}
		else
		{
			tmp = invalid_token(line, i);
			if (!tmp || tmp[0] != '\0')
				return (tmp);
		}
		i++;
	}
	return (ft_strdup(""));
}

int	invalid_syntax(char *line)
{
	char	*token;
	char	*new_line;

	new_line = remove_whitespace(line);
	if (!new_line)
		return (EXIT_FAILURE);
	token = check_token(new_line);
	if (!token)
	{
		ft_free((void **)&new_line);
		return (EXIT_FAILURE);
	}
	if (token[0] != '\0')
	{
		printf(SYNTAXE_ERROR, token);
		ft_free((void **)&new_line);
		ft_free((void **)&token);
		return (EXIT_FAILURE);
	}
	ft_free((void **)&token);
	ft_free((void **)&new_line);
	return (EXIT_SUCCESS);
}
