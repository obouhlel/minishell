#include "minishell.h"

void ft_free_envp(t_envp *envp)
{
    t_envp  *tmp;

    while (envp)
    {
        tmp = envp;
        envp = envp->next;
        ft_free((void **)&tmp->key);
        ft_free((void **)&tmp->value);
        ft_free((void **)&tmp);
    }
}