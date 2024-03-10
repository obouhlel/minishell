/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stle-gof <stle-gof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 08:22:09 by stle-gof          #+#    #+#             */
/*   Updated: 2024/03/10 09:17:08 by stle-gof         ###   ########.fr       */
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
int		do_expend(size_t *j, char *line, char **new_line, t_envp *envp);
size_t	count_dolars(char *line);
char	*get_var(char *str);
bool	can_do_expend(char c, char c_next, bool is_in_sigle_quote);
size_t	count_size_new_line(char *line, t_envp *envp);
void	check_quote_state(char cur_char, bool *is_single, bool *is_double);

#endif