#include "minishell.h"
#include "parsing.h"

t_input *parsing(char *line, t_envp *envp)
{
    char    invalid_token;

    (void)envp;
    invalid_token = have_invalid_token(line);
    if (invalid_token)
    {
        if (invalid_token == '\n')
            printf("minishell: syntax error near unexpected token `newline'\n");
        else
            printf("minishell: syntax error near unexpected token `%c'\n", invalid_token);
        return (NULL);
    }
    return (NULL);
}