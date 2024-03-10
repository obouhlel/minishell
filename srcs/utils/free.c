/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ultils_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stle-gof <stle-gof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 09:50:45 by stle-gof          #+#    #+#             */
/*   Updated: 2024/03/10 09:51:53 by stle-gof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
