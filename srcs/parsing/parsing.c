/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <obouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 10:30:28 by obouhlel          #+#    #+#             */
/*   Updated: 2024/03/10 15:03:28 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

t_input	*parsing(char *line, t_envp *envp)
{
	char	invalid_token;
	char	*new_line;
	t_input	*input;

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
	input = tokenisation(new_line);
	if (!input)
		return (NULL);
	ft_free((void **)&new_line);
	return (NULL);
}

void	check_quote_state(char cur_char, bool *is_single, bool *is_double)
{
	if (cur_char == '\"' && !(*is_single))
		*is_double = !(*is_double);
	if (cur_char == '\'' && !(*is_double))
		*is_single = !(*is_single);
}
