/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <obouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 09:50:45 by stle-gof          #+#    #+#             */
/*   Updated: 2024/03/11 15:24:51 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

void	ft_free(void **ptr)
{
	if (*ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

void	ft_free_strs(char ***strs)
{
	size_t	i;

	i = 0;
	if (!*strs)
		return ;
	while ((*strs)[i])
	{
		ft_free((void **)&(*strs)[i]);
		i++;
	}
	free(*strs);
	*strs = NULL;
}

void	ft_free_input(t_input *input)
{
	t_input	*tmp;

	while (input)
	{
		tmp = input;
		input = input->next;
		ft_free((void **)&tmp->str);
		ft_free((void **)&tmp);
	}
}
