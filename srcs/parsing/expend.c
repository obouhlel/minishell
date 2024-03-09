#include "minishell.h"
#include "parsing.h"

char    *expend(char *line, t_envp *envp)
{
    // char    *new_line;

    (void)envp;
    count_dolars(line);
    return ("toto");
}