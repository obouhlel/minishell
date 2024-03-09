#include "minishell.h"

char    *envp_get(t_envp *envp, char *key)
{
    t_envp *tmp;

    tmp = envp;
    while (tmp)
    {
        if (strcmp(tmp->key, key) == 0)
            return (ft_strdup(tmp->value));
        tmp = tmp->next;
    }
    return (ft_strdup("\0"));
}
