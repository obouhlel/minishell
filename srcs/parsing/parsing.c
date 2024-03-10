/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <obouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 08:22:44 by stle-gof          #+#    #+#             */
/*   Updated: 2024/03/10 10:00:41 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

t_input	*parsing(char *line, t_envp *envp)
{
	char invalid_token;
	char *new_line;

	invalid_token = have_invalid_token(line);
	if (invalid_token != '\0')
	{
		if (invalid_token == '\n')
			printf("minishell: syntax error near unexpected token `newline'\n");
		else
			printf("minishell: syntax error near unexpected token `%c'\n",
				invalid_token);
		return (NULL);
	}
	new_line = expend(line, envp);
	if (!new_line)
		return (NULL);
	printf("new_line: %s\n", new_line);
	printf("nb_token: %zu\n", count_nb_token(new_line));
	ft_free((void **)&new_line);
	return (NULL);
}