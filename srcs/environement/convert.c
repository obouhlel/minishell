/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stle-gof <stle-gof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 08:22:17 by stle-gof          #+#    #+#             */
/*   Updated: 2024/03/10 10:22:38 by stle-gof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	envp_size(t_envp *envp)
{
	size_t	size;

	size = 0;
	while (envp)
	{
		size++;
		envp = envp->next;
	}
	return (size);
}

char	*ft_join_env(char *key, char *value)
{
	char	*env;
	size_t	i;
	size_t	j;

	env = calloc(sizeof(char), (ft_strlen(key) + ft_strlen(value) + 2));
	if (!env)
		return (NULL);
	i = 0;
	while (key[i])
	{
		env[i] = key[i];
		i++;
	}
	env[i] = '=';
	i++;
	j = 0;
	while (value[j])
	{
		env[i + j] = value[j];
		j++;
	}
	return (env);
}

char	**envp_to_tab(t_envp *envp)
{
	char	**tab;
	int		i;

	tab = calloc(sizeof(char *), (envp_size(envp) + 1));
	if (!tab)
		return (NULL);
	i = 0;
	if (envp && strcmp(envp->key, "?") == 0)
		envp = envp->next;
	while (envp)
	{
		tab[i] = ft_join_env(envp->key, envp->value);
		if (!tab[i])
		{
			ft_free_strs(&tab);
			return (NULL);
		}
		envp = envp->next;
		i++;
	}
	return (tab);
}
