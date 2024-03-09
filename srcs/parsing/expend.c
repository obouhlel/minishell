#include "minishell.h"
#include "parsing.h"

int     do_expend(size_t *j, char *line, char **new_line, t_envp *envp)
{
    char    *var;
    char    *value;
    size_t  i;

    var = get_var(line);
    if (!var)
        return (EXIT_FAILURE);
    value = envp_get(envp, var);
    if (!value)
        return (ft_free((void **)&var), EXIT_FAILURE);
    i = 0;
    while (value[i])
    {
        (*new_line)[*j] = value[i];
        i++;
        (*j)++;
    }
    ft_free((void **)&var);
    ft_free((void **)&value);
    return (EXIT_SUCCESS);
}

char    *expend(char *line, t_envp *envp)
{
    const size_t    len = count_size_new_line(line, envp);
    char            *new_line;
    size_t          i;
    size_t          j;
    bool            is_in_sigle_quote;
    bool            is_in_double_quote;

    if (count_dolars(line) == 0)
        return (ft_strdup(line));
    new_line = calloc(sizeof(char), (len + 1));
    if (!new_line)
        return (NULL);
    i = 0;
    j = 0;
    while (line[i])
    {
        if (line[i] == '\"' && is_in_sigle_quote == false)
            is_in_double_quote = !is_in_double_quote;
        if (line[i] == '\'' && is_in_double_quote == false)
            is_in_sigle_quote = !is_in_sigle_quote;
        if (can_do_expend(line[i], line[i + 1], is_in_sigle_quote))
        {
            do_expend(&j, &line[++i], &new_line, envp);
            while (line[i] && (is_var(line[i]) || line[i] == '?'))
                i++;
            if (line[i] == '\0')
                break ;
        }
        new_line[j] = line[i];
        i++;
        j++;
    }
    return (new_line);
}