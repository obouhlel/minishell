#include "minishell.h"

void	envp_update(t_envp **envp, char *key, char *value)
{
    t_envp *tmp;

    tmp = *envp;
    while (tmp)
	{
		if (strcmp(tmp->key, key) == 0)
		{
			free(tmp->value);
			tmp->value = value;
			return ;
		}
		tmp = tmp->next;
	}
}
