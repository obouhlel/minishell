/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expend_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <obouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 08:22:35 by stle-gof          #+#    #+#             */
/*   Updated: 2024/03/11 15:32:24 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

bool	can_do_expend(char c, char c_next, bool is_single)
{
	return (c == '$' && c_next != '\0' && !is_whitespace(c_next) && !is_single);
}

size_t	count_dolars(char *line)
{
	size_t	i;
	size_t	count;
	bool	is_single;
	bool	is_double;

	i = 0;
	count = 0;
	is_single = false;
	is_double = false;
	while (line[i])
	{
		check_quote_state(line[i], &is_single, &is_double);
		if (can_do_expend(line[i], line[i + 1], is_single))
			count++;
		i++;
	}
	return (count);
}

char	*get_var(char *str)
{
	char	*var;
	size_t	i;

	if (str[0] == '?')
		return (ft_strdup("?"));
	if (!is_alpha(str[0]))
		return (ft_strdup("\0"));
	i = 0;
	while (str[i] && is_var(str[i]))
		i++;
	var = calloc(sizeof(char), (i + 1));
	if (!var)
		return (NULL);
	i = 0;
	while (str[i] && is_var(str[i]))
	{
		var[i] = str[i];
		i++;
	}
	return (var);
}

int	count_expend_size(char *line, t_envp *envp, size_t *i)
{
	int		size;
	char	*var;
	char	*value;

	size = 0;
	var = get_var(line);
	if (!var)
		return (-1);
	*i += ft_strlen(var);
	value = envp_get(envp, var);
	if (!value)
		return (-1);
	size = ft_strlen(value);
	ft_free((void **)&var);
	ft_free((void **)&value);
	return (size);
}

size_t	count_size_new_line(char *line, t_envp *envp)
{
	size_t		i;
	size_t		size;
	int			check_size;
	t_expand	exp;

	i = 0;
	size = 0;
	bzero(&exp, sizeof(t_expand));
	while (line[i])
	{
		check_quote_state(line[i], &exp.is_single, &exp.is_double);
		if (can_do_expend(line[i], line[i + 1], exp.is_single))
		{
			check_size = count_expend_size(&line[++i], envp, &i);
			if (check_size == -1)
				return (0);
			size += check_size;
		}
		else
		{
			size++;
			i++;
		}
	}
	return (size);
}
