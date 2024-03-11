/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <obouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 08:22:09 by stle-gof          #+#    #+#             */
/*   Updated: 2024/03/11 10:57:37 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>

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
}	t_parsing;

char		have_invalid_token(char *line);
char		*expend(char *line, t_envp *envp);
t_input		*tokenisation(char *line);

// EXPEND
int			do_expend(size_t *j, char *line, char **new_line, t_envp *envp);
size_t		count_dolars(char *line);
char		*get_var(char *str);
bool		can_do_expend(char c, char c_next, bool is_in_sigle_quote);
size_t		count_size_new_line(char *line, t_envp *envp);
void		check_quote_state(char cur_char, bool *is_single, bool *is_double);

void		ft_free_parsing(t_parsing *parse, bool free_str);

#endif