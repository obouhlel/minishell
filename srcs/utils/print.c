/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <obouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 18:40:07 by obouhlel          #+#    #+#             */
/*   Updated: 2024/03/12 18:42:10 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_putchar_fd(char c, int fd)
{
    return (write(fd, &c, 1));
}

int ft_putstr_fd(char *s, int fd)
{
    return (write(fd, s, ft_strlen(s)));
}

int ft_putendl_fd(char *s, int fd)
{
    int ret;

    ret = ft_putstr_fd(s, fd);
    if (ret == -1)
        return (ret);
    ret = ft_putchar_fd('\n', fd);
    if (ret == -1)
        return (ret);
    return (ret);
}
