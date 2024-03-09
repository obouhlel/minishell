#ifndef PARSING_H
#define PARSING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char    have_invalid_token(char *line);
char    *expend(char *line, t_envp *envp);

// EXPEND
size_t  count_dolars(char *line);
char    *get_var(char *str);
bool    do_expend(char c, char c_next, bool is_in_sigle_quote);
size_t  count_size_new_line(char *line, t_envp *envp);
#endif