#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdbool.h>

bool    is_whitespace(char c)
{
    return (c == ' ' || c == '\t' || c == '\n');
}

bool    is_empty(char *str)
{
    size_t i;

    i = 0;
    while (str[i])
    {
        if (!is_whitespace(str[i]))
            return (false);
        i++;
    }
    return (true);
}

int minishell(t_envp *envp)
{
    char *line;

    (void)envp;
    while (1)
    {
        line = readline("> ");
        if (!line)
            return (ft_free((void **)&line), EXIT_FAILURE);
        if (is_empty(line))
        {
            ft_free((void **)&line);
            continue ;
        }
        add_history(line);
    }
    return (EXIT_SUCCESS);
}