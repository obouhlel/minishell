/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <obouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 11:35:30 by obouhlel          #+#    #+#             */
/*   Updated: 2024/03/11 15:26:13 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

static
char	*get_type(int token)
{
	if (token == WORD)
		return ("WORD");
	if (token == PIPES)
		return ("PIPES");
	if (token == REDIR)
		return ("REDIR");
	return ("UNKNOWN");
}

static
char	*to_join_bool(bool to_join)
{
	if (to_join)
		return ("true");
	return ("false");
}

void	print_parse(t_parsing *parse)
{
	while (parse)
	{
		printf("str: %s | type: %s | to join: %s\n", \
			parse->str, \
			get_type(parse->token), \
			to_join_bool(parse->to_join));
		parse = parse->next;
	}
}
