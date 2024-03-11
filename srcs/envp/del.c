/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stle-gof <stle-gof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 08:22:20 by stle-gof          #+#    #+#             */
/*   Updated: 2024/03/10 10:21:45 by stle-gof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	envp_del(t_envp **envp, char *key)
{
	t_envp	*tmp;
	t_envp	*prev;

	tmp = *envp;
	prev = NULL;
	while (tmp && strcmp(tmp->key, key) != 0)
	{
		prev = tmp;
		tmp = tmp->next;
	}
	if (tmp == NULL)
		return ;
	if (tmp == *envp)
		*envp = tmp->next;
	else
		prev->next = tmp->next;
	free(tmp->key);
	free(tmp->value);
	free(tmp);
}
