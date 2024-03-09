#include "minishell.h"

size_t ft_strlen(char *str)
{
    size_t i;

    i = 0;
    while (str[i])
        i++;
    return (i);
}

size_t ft_strlen_c(char *str, char c)
{
	size_t i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

size_t size_strs(char **tab)
{
	size_t i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

void ft_free(void **ptr)
{
    if (*ptr)
    {
        free(*ptr);
        *ptr = NULL;
    }
}

void ft_free_strs(char ***strs)
{
    size_t i;

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

char    *ft_strdup(char *str)
{
    char    *dup;
    size_t  i;

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