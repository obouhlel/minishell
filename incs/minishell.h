#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>

typedef struct s_envp
{
	char			*key;
	char			*value;
	struct s_envp	*next;
}   t_envp;

typedef struct s_input
{
	char	*str;
	int		token;
	struct s_input	*next;
}	t_input;

int		minishell(t_envp *envp);
t_input	*parsing(t_envp *envp);

// ENV
t_envp	*envp_init(char **env);
int		envp_add(t_envp **envp, char *key, char *value);
void	envp_del(t_envp **envp, char *key);
char	*envp_get(t_envp *envp, char *key);
void	envp_update(t_envp **envp, char *key, char *value);
void	print_envp(t_envp *envp);
void	ft_free_envp(t_envp *envp);

// UTILS
size_t	ft_strlen_c(char *str, char c);
size_t	ft_strlen(char *str);
size_t	size_tab(char **tab);
void	ft_free(void **ptr);
char	*ft_strdup(char *str);

#endif