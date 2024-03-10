/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhlel <obouhlel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 08:22:09 by stle-gof          #+#    #+#             */
/*   Updated: 2024/03/10 10:27:56 by obouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>

char	have_invalid_token(char *line);
char	*expend(char *line, t_envp *envp);

// EXPEND
size_t	count_nb_token(char *line);
int		do_expend(size_t *j, char *line, char **new_line, t_envp *envp);
size_t	count_dolars(char *line);
char	*get_var(char *str);
bool	can_do_expend(char c, char c_next, bool is_in_sigle_quote);
size_t	count_size_new_line(char *line, t_envp *envp);
#endif