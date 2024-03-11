/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <obouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 08:22:09 by stle-gof          #+#    #+#             */
/*   Updated: 2024/03/11 17:02:52 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>

# define SYNTAXE_ERROR "minishell: syntax error near unexpected token `%s'\n"

typedef struct s_input	t_input;
typedef struct s_envp	t_envp;

enum e_quote
{
	SINGLE,
	DOUBLE,
};

enum e_type
{
	WORD,
	REDIR,
	PIPES,
};

typedef struct s_expand
{
	size_t	i;
	size_t	j;
	bool	is_single;
	bool	is_double;
	char	*new_line;
}			t_expand;

typedef struct s_parsing
{
	char				*str;
	int					token;
	bool				to_join;
	struct s_parsing	*prev;
	struct s_parsing	*next;
}			t_parsing;

int			invalid_syntax(char *line);
char		*expend(char *line, t_envp *envp);
t_input		*tokenisation(char *line);

// syntaxe_error_utils
char		*remove_whitespace(char *line);
int			is_in_quotes(char *line, size_t *i, char quote);
char		*syntaxe_redir(char *line, size_t i, char redir);
char		*invalid_token(char *line, size_t i);
bool		error_syntaxe_pipe(char *line, size_t i);

// expend
int			do_expend(size_t *j, char *line, char **new_line, t_envp *envp);
// expend utils
size_t		count_dolars(char *line);
char		*get_var(char *str);
bool		can_do_expend(char c, char c_next, bool is_in_sigle_quote);
size_t		count_size_new_line(char *line, t_envp *envp);
void		check_quote_state(char cur_char, bool *is_single, bool *is_double);

// pre tokenisation
t_parsing	*pre_tokenisation(char *line);
// tokenisation utils add
int			parsing_add(t_parsing **parse, char *str, int token, bool to_join);
int			input_add(t_input **input, char *str, int token);
// tokenisation utils
int			is_type(char c);
int			join_word(t_parsing *parse);
int			join_parsing(t_parsing **parse);
char		*redir_string(char *line, int *i, char c, char *redir);
void		ft_free_parsing(t_parsing *parse, bool free_str);

#endif