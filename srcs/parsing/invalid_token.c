#include "minishell.h"
#include "parsing.h"

int is_in_quotes(char *line, size_t *i, char quote)
{
    size_t  j;

    j = *i + 1;
    if (line[j] == '\0')
        return (EXIT_FAILURE);
    while (line[j] && line[j] != quote)
        j++;
    if (!line[j])
        return (EXIT_FAILURE);
    *i = j;
    return (EXIT_SUCCESS);
}

char    check_redirection(char *line, size_t *i, char c, size_t size)
{
    const char *invalid_token = "|<>";
    size_t  j;

    j = *i;
    if (line[j] != c)
        return ('\0');
    while (line[j] && line[j] == c)
        j++;
    if (j - *i > size)
        return (c);
    if (line[j] == '\0')
        return ('\n');
    if (strchr(invalid_token, line[j]))
        return (line[j]);
    *i = j - 1;
    return ('\0');
}

char    have_invalid_token(char *line)
{
    const char  *invalid_token = ";\\^&*(){}[]_-`~@#%/.,:";
    char        c;
    size_t      i;

    i = 0;
    if (line[i] == '|')
        return ('|');
    while (line[i])
    {
        if (line[i] == '\'' || line[i] == '\"')
        {
            c = line[i];
            if (is_in_quotes(line, &i, c) == EXIT_FAILURE)
                return (c);
            if (line[i] == '\0')
                break ;
        }
        c = check_redirection(line, &i, '>', 2);
        if (c)
            return (c);
        c = check_redirection(line, &i, '<', 2);
        if (c)
            return (c);
        c = check_redirection(line, &i, '|', 1);
        if (c)
            return (c);
        if (strchr(invalid_token, line[i]))
            return (line[i]);
        i++;
    }
    return ('\0');
}

