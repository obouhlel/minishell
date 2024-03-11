/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <obouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 08:22:52 by stle-gof          #+#    #+#             */
/*   Updated: 2024/03/11 15:24:34 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_alpha(char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

bool	is_alpha_num(char c)
{
	return (is_alpha(c) || (c >= '0' && c <= '9'));
}

bool	is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

bool	is_var(char c)
{
	return (is_alpha_num(c) || c == '_');
}

bool	is_quote(char c)
{
	return (c == '\'' || c == '\"');
}
