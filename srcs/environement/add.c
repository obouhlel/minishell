#include "minishell.h"

static t_envp *last_envp(t_envp *envp)
{
    if (envp == NULL)
        return NULL;

    while (envp->next)
        envp = envp->next;

    return envp;
}

int envp_add(t_envp **envp, char *key, char *value)
{
	t_envp	*new;
	t_envp	*last;

	if (!key || !value)
		return (EXIT_FAILURE);
	last = last_envp(*envp);
	new = calloc(sizeof(t_envp), 1);
	if (!new)
		return (EXIT_FAILURE);
	new->key = key;
	new->value = value;
	new->next = NULL;
	if (!(*envp))
		*envp = new;
	else if (last)
		last->next = new;
	return (EXIT_SUCCESS);
}