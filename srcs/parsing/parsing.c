/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <obouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 10:30:28 by obouhlel          #+#    #+#             */
/*   Updated: 2024/03/11 12:36:46 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

t_input	*parsing(char *line, t_envp *envp)
{
	char		invalid_token;
	char		*new_line;
	t_input		*input;

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
		return (ft_free((void **)&line), NULL);
	ft_free((void **)&line);
	input = tokenisation(new_line);
	if (!input)
		return (ft_free((void **)&new_line), NULL);
	ft_free((void **)&new_line);
	return (input);
}

void	check_quote_state(char cur_char, bool *is_single, bool *is_double)
{
	if (cur_char == '\"' && !(*is_single))
		*is_double = !(*is_double);
	if (cur_char == '\'' && !(*is_double))
		*is_single = !(*is_single);
}

static
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
	return ("WAS IST DAS?!");
}

void	print_input(t_input *input)
{
	while (input)
	{
		printf("%s | %s\n", input->str, get_token(input->token));
		input = input->next;
	}
}
