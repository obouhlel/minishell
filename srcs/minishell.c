/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <obouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 07:58:00 by stle-gof          #+#    #+#             */
/*   Updated: 2024/03/11 16:55:31 by obouhlel         ###   ########.fr       */
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
	t_shell	shell;

	shell.envp = envp;
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
		shell.input = parsing(line, envp);
		if (!shell.input)
			continue ;
		print_input(shell.input);
		ft_free_input(shell.input);
	}
	return (EXIT_SUCCESS);
}
