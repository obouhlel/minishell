/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <obouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 08:22:05 by stle-gof          #+#    #+#             */
/*   Updated: 2024/03/11 11:31:16 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdbool.h>
# include <string.h>

enum e_token
{
	CMD,
	ARG,
	PIPE,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_IN,
	HEREDOC,
	OUTFILE,
	APPEND,
	INFILE,
	DELIMETER,
};

typedef struct s_envp
{
	char			*key;
	char			*value;
	struct s_envp	*next;
}					t_envp;

typedef struct s_input
{
	char			*str;
	int				token;
	struct s_input	*next;
}					t_input;

typedef struct s_shell
{
	t_envp		*envp;
	t_input		*input;
}				t_shell;

int			minishell(t_envp *envp);
t_input		*parsing(char *line, t_envp *envp);

// ENV
t_envp	*envp_init(char **env);
int		envp_add(t_envp **envp, char *key, char *value);
void	envp_del(t_envp **envp, char *key);
char	*envp_get(t_envp *envp, char *key);
void	envp_update(t_envp **envp, char *key, char *value);
void	print_envp(t_envp *envp);
char	**envp_to_tab(t_envp *envp);
void	ft_free_envp(t_envp *envp);

// UTILS
size_t	ft_strlen_c(char *str, char c);
size_t	ft_strlen(char *str);
size_t	size_strs(char **strs);
void	ft_free(void **ptr);
void	ft_free_strs(char ***strs);
void	ft_free_input(t_input *input);
char	*ft_strdup(char *str);
bool	is_alpha(char c);
bool	is_alpha_num(char c);
bool	is_whitespace(char c);
bool	is_var(char c);
bool	is_quote(char c);
char	*ft_strjoin(char *str1, char *str2);
void	print_input(t_input *input);

#endif