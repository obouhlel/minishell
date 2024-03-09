#include "minishell.h"
#include "parsing.h"

bool    can_do_expend(char c, char c_next, bool is_in_sigle_quote)
{
    return (c == '$' && c_next != '\0' && \
        !is_whitespace(c_next) && !is_in_sigle_quote);
}

size_t  count_dolars(char *line)
{
    size_t  i;
    size_t  count;
    bool    is_in_sigle_quote;
    bool    is_in_double_quote;

    i = 0;
    count = 0;
    is_in_sigle_quote = false;
    is_in_double_quote = false;
    while (line[i])
    {
        if (line[i] == '\"' && is_in_sigle_quote == false)
            is_in_double_quote = !is_in_double_quote;
        if (line[i] == '\'' && is_in_double_quote == false)
            is_in_sigle_quote = !is_in_sigle_quote;
        if (can_do_expend(line[i], line[i + 1], is_in_sigle_quote))
            count++;
        i++;
    }
    return (count);
}

char    *get_var(char *str)
{
    char    *var;
    size_t  i;

    if (str[0] == '?')
        return (ft_strdup("?"));
    if (!is_alpha(str[0]))
        return (ft_strdup("\0"));
    i = 0;
    while(str[i] && is_var(str[i]))
        i++;
    var = calloc(sizeof(char), (i + 1));
    if (!var)
        return (NULL);
    i = 0;
    while (str[i] && is_var(str[i]))
    {
        var[i] = str[i];
        i++;
    }
    return (var);
}

int  count_expend_size(char *line, t_envp *envp)
{
    int     size;
    char    *var;
    char    *value;

    size = 0;
    var = get_var(line);
    if (!var)
        return (-1);
    value = envp_get(envp, var);
    if (!value)
        return (-1);
    size = ft_strlen(value);
    ft_free((void **)&var);
    ft_free((void **)&value);
    return (size);
}


size_t  count_size_new_line(char *line, t_envp *envp)
{
    size_t  i;
    size_t  size;
    bool    is_in_sigle_quote;
    bool    is_in_double_quote;
    int     check_size;

    i = -1;
    size = 0;
    is_in_sigle_quote = false;
    is_in_double_quote = false;
    while (line[++i])
    {
        if (line[i] == '\"' && is_in_sigle_quote == false)
            is_in_double_quote = !is_in_double_quote;
        if (line[i] == '\'' && is_in_double_quote == false)
            is_in_sigle_quote = !is_in_sigle_quote;
        if (can_do_expend(line[i], line[i + 1], is_in_sigle_quote))
        {
            i++;
            check_size = count_expend_size(&line[i], envp);
            if (check_size == -1)
                return (0);
            size += check_size;
        }
        else
            size++;
    }
    return (size);
}