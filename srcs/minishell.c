/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <obouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 07:58:00 by stle-gof          #+#    #+#             */
/*   Updated: 2024/03/10 13:15:27 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/history.h>
#include <readline/readline.h>

bool	is_empty(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (!is_whitespace(str[i]))
			return (false);
		i++;
	}
	return (true);
}

int	minishell(t_envp *envp)
{
	char	*line;
	t_input	*input;

	while (1)
	{
		line = readline("> ");
		if (!line)
			return (EXIT_FAILURE);
		if (is_empty(line))
		{
			ft_free((void **)&line);
			continue ;
		}
		add_history(line);
		input = parsing(line, envp);
		if (!input)
		{
			ft_free((void **)&line);
			continue ;
		}
		ft_free_input(input);
		ft_free((void **)&line);
	}
	return (EXIT_SUCCESS);
}
