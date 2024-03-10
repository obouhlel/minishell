/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stle-gof <stle-gof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 08:22:29 by stle-gof          #+#    #+#             */
/*   Updated: 2024/03/10 08:22:30 by stle-gof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_envp(t_envp *envp)
{
	while (envp)
	{
		printf("%s=%s\n", envp->key, envp->value);
		envp = envp->next;
	}
}