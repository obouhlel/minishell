/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stle-gof <stle-gof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 08:22:27 by stle-gof          #+#    #+#             */
/*   Updated: 2024/03/10 08:22:28 by stle-gof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*envp_get(t_envp *envp, char *key)
{
	t_envp	*tmp;

	tmp = envp;
	while (tmp)
	{
		if (strcmp(tmp->key, key) == 0)
			return (ft_strdup(tmp->value));
		tmp = tmp->next;
	}
	return (ft_strdup("\0"));
}
