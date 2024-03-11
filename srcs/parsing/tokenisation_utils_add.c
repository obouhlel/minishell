/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation_utils_add.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <obouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 17:02:22 by obouhlel          #+#    #+#             */
/*   Updated: 2024/03/11 17:02:31 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

int	parsing_add(t_parsing **parse, char *str, int token, bool to_join)
{
	t_parsing		*new_node;
	t_parsing		*current;

	if (!str)
		return (EXIT_FAILURE);
	new_node = (t_parsing *)calloc(sizeof(t_parsing), 1);
	if (!new_node)
		return (EXIT_FAILURE);
	new_node->str = str;
	new_node->token = token;
	new_node->to_join = to_join;
	new_node->next = NULL;
	new_node->prev = NULL;
	if (*parse == NULL)
		*parse = new_node;
	else
	{
		current = *parse;
		while (current->next != NULL)
			current = current->next;
		current->next = new_node;
	}
	return (EXIT_SUCCESS);
}

int	input_add(t_input **input, char *str, int token)
{
	t_input		*new_node;
	t_input		*current;

	if (!str)
		return (EXIT_FAILURE);
	new_node = (t_input *)calloc(sizeof(t_input), 1);
	if (!new_node)
		return (EXIT_FAILURE);
	new_node->str = str;
	new_node->token = token;
	new_node->next = NULL;
	if (*input == NULL)
		*input = new_node;
	else
	{
		current = *input;
		while (current->next != NULL)
			current = current->next;
		current->next = new_node;
	}
	return (EXIT_SUCCESS);
}
