#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

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
    char    *line;
    t_input *input;

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
        input = parsing(line, envp);
        if (!input)
        {
            ft_free((void **)&line);
            continue ;
        }
        ft_free((void **)&line);
    }
    return (EXIT_SUCCESS);
}