/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <obouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 09:46:45 by stle-gof          #+#    #+#             */
/*   Updated: 2024/03/11 16:57:45 by obouhlel         ###   ########.fr       */
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
	char	*new_str;
	size_t	i;
	size_t	j;

	new_str = calloc(sizeof(char), (ft_strlen(str1) + ft_strlen(str2) + 1));
	if (!new_str)
		return (NULL);
	i = 0;
	while (str1[i])
	{
		new_str[i] = str1[i];
		i++;
	}
	j = 0;
	while (str2[j])
	{
		new_str[i] = str2[j];
		i++;
		j++;
	}
	return (new_str);
}

char	*ft_substr(char *str, size_t start, size_t len)
{
	char	*sub_str;
	size_t	i;

	sub_str = calloc(sizeof(char), (len + 1));
	if (!sub_str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		sub_str[i] = str[start + i];
		i++;
	}
	return (sub_str);
}
