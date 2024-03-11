/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <obouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 09:46:45 by stle-gof          #+#    #+#             */
/*   Updated: 2024/03/11 09:44:06 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strdup(char *str)
{
	char	*dup;
	size_t	i;

	dup = calloc(sizeof(char), (ft_strlen(str) + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (str[i])
	{
		dup[i] = str[i];
		i++;
	}
	return (dup);
}

char	*ft_strjoin(char *str1, char *str2)
{
	char	*tmp;
	char	*new_str;
	size_t	i;
	size_t	j;

	tmp = ft_strdup(str1);
	if (!tmp)
		return (NULL);
	new_str = calloc(sizeof(char), (ft_strlen(str1) + ft_strlen(str2) + 1));
	if (!new_str)
		return (NULL);
	i = 0;
	while (str2[i])
	{
		new_str[i] = str2[i];
		i++;
	}
	j = 0;
	while (tmp[j])
	{
		new_str[i] = tmp[j];
		i++;
		j++;
	}
	free(tmp);
	return (new_str);
}
