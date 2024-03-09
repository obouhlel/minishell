#include "minishell.h"

void print_envp(t_envp *envp)
{
    while (envp)
    {
        printf("%s=%s\n", envp->key, envp->value);
        envp = envp->next;
    }
}