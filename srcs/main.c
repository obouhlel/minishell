#include "minishell.h"

int main(int ac, char **av, char **env)
{
	t_envp	*envp;
	char	**tab;

	(void)ac;
	(void)av;
	envp = envp_init(env);
	if (!envp)
		return (EXIT_FAILURE);
	// minishell(envp);
	tab = envp_to_tab(envp);
	ft_free_envp(envp);
	return (EXIT_SUCCESS);
}