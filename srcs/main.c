#include "minishell.h"

int main(int ac, char **av, char **env)
{
	t_envp	*envp;

	(void)ac;
	(void)av;
	envp = envp_init(env);
	if (!envp)
		return (EXIT_FAILURE);
	minishell(envp);
	ft_free_envp(envp);
	return (EXIT_SUCCESS);
}