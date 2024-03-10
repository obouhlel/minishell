/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expend.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stle-gof <stle-gof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 08:22:39 by stle-gof          #+#    #+#             */
/*   Updated: 2024/03/10 08:29:47 by stle-gof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

int	do_expend(size_t *j, char *line, char **new_line, t_envp *envp)
{
	char	*var;
	char	*value;
	size_t	i;

	var = get_var(line);
	if (!var)
		return (EXIT_FAILURE);
	value = envp_get(envp, var);
	if (!value)
		return (ft_free((void **)&var), EXIT_FAILURE);
	i = 0;
	while (value[i])
	{
		(*new_line)[*j] = value[i];
		i++;
		(*j)++;
	}
	ft_free((void **)&var);
	ft_free((void **)&value);
	return (EXIT_SUCCESS);
}


void	expand_variable(char *line, t_envp *envp, t_expand *exp)
{
	do_expend(&(exp->j), &line[++(exp->i)], &(exp->new_line), envp);
	while (line[exp->i] && (is_var(line[exp->i]) || line[exp->i] == '?'))
		exp->i++;
	if (line[exp->i] == '\0')
		return ;
	exp->i--;
}

char	*expand(char *line, t_envp *envp)
{
	const size_t	len = count_size_new_line(line, envp);
	t_expand		exp;

	if (count_dollars(line) == 0)
		return (ft_strdup(line));
	bzero(&exp, sizeof(t_expand));
	exp.new_line = calloc(sizeof(char), (len + 1));
	if (!exp.new_line)
		return (NULL);
	while (line[exp.i])
	{
		if (line[exp.i] == '\"' && !exp.is_in_single_quote)
			exp.is_in_double_quote = !exp.is_in_double_quote;
		else if (line[exp.i] == '\'' && !exp.is_in_double_quote)
			exp.is_in_single_quote = !exp.is_in_single_quote;
		else if (can_do_expand(line[exp.i], line[exp.i + 1],
				exp.is_in_single_quote))
			expand_variable(line, envp, &exp);
		else
			exp.new_line[exp.j++] = line[exp.i];
		exp.i++;
	}
	return (exp.new_line);
}