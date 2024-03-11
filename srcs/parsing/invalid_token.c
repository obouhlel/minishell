/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invalid_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <obouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 10:30:10 by obouhlel          #+#    #+#             */
/*   Updated: 2024/03/11 15:34:08 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

// static
// int	is_in_quotes(char *line, size_t *i, char quote)
// {
// 	size_t	j;

// 	j = *i + 1;
// 	if (line[j] == '\0')
// 		return (EXIT_FAILURE);
// 	while (line[j] && line[j] != quote)
// 		j++;
// 	if (!line[j])
// 		return (EXIT_FAILURE);
// 	*i = j;
// 	return (EXIT_SUCCESS);
// }

int	invalid_syntax(char *line)
{
	char	*token;

	(void)line;
	printf(SYNTAXE_ERROR, token);
	return (EXIT_SUCCESS);
}
