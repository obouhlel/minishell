/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <obouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 07:49:41 by stle-gof          #+#    #+#             */
/*   Updated: 2024/03/12 18:47:05 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	t_envp	*envp;

	(void)ac;
	(void)av;
	envp = envp_init(env);
	if (!envp)
		return (EXIT_FAILURE);
	minishell(envp);
	ft_free_envp(envp);
	return (EXIT_SUCCESS);
}
