#include "minishell.h"

char *get_key(char *str)
{
	char	*key;
	size_t	i;

	key = calloc(sizeof(char), (ft_strlen_c(str, '=') + 1));
	if (!key)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '=')
	{
		key[i] = str[i];
		i++;
	}
	return (key);
}

char *get_value(char *str)
{
	char	*value;
	size_t	skip_char;
	size_t	i;

	skip_char = ft_strlen_c(str, '=') + 1;
	value = calloc(sizeof(char), (ft_strlen(str) - skip_char + 1));
	if (!value)
		return (NULL);
	i = 0;
	while (str[skip_char + i])
	{
		value[i] = str[skip_char + i];
		i++;
	}
	return (value);
}

void add_exit_code(t_envp **envp)
{
	char	*key;
	char	*value;
	int	 status;

	key = ft_strdup("?");
	if (!key)
		return ;
	value = ft_strdup("0");
	if (!value)
	{
		ft_free((void **)&key);
		return ;
	}
	status = envp_add(envp, key, value);
	if (status == EXIT_FAILURE)
	{
		ft_free((void **)&key);
		ft_free((void **)&value);
	}
}

t_envp *envp_init(char **env)
{
	t_envp  *envp;
	int		status;
	int		i;

	envp = NULL;
	status = 0;
	i = 0;
	add_exit_code(&envp);
	if (!envp)
		return (NULL);
	while (env[i])
	{
		status = envp_add(&envp, get_key(env[i]), get_value(env[i]));
		if (status == EXIT_FAILURE)
			return (ft_free_envp(envp), NULL);
		i++;
	}
	return (envp);
}