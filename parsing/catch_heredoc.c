#include "../mandatory/minishell.h"

static char *append_line(char *str, char *line, t_all *all)
{
    size_t line_len;
    size_t new_len;
    char  *new_str;
    
    if (line == NULL)
    return (str);
    line_len = ft_strlen(line);
    new_len = all->hd_data.str_len + line_len + 2;
    // new_len = all->hd_data.str_len + line_len + 1;
    new_str = gc_malloc(all, new_len);
    if (new_str == NULL)
    return (NULL);
    if (all->hd_data.str_len > 0 && str != NULL)
    ft_memcpy(new_str, str, all->hd_data.str_len);
    ft_memcpy(new_str + all->hd_data.str_len, line, line_len);
    new_str[all->hd_data.str_len + line_len] = '\n';
    new_str[all->hd_data.str_len + line_len + 1] = '\0';
    all->hd_data.str_len = all->hd_data.str_len + line_len + 1;
    return (new_str);
}

static char *process_input_lines(char *str, char *hd_eof, t_all *all)
{
    char *line;
    char *new_str;

    while (1)
    {
        line = readline("heredoc:");
        if (line == NULL)
            break;
        if (ft_strncmp(line, hd_eof, all->hd_data.hd_eof_len) == 0 &&
            ft_strlen(line) == all->hd_data.hd_eof_len)
        {
            free(line);
            break;
        }
        new_str = append_line(str, line, all);
        if (new_str == NULL)
            break;
        str = new_str;
        free(line);
    }
    return (str);
}

char *append_hd(char *hd_eof, t_all *all)
{
    char *str;

    str = gc_malloc(all, sizeof(char) * 1);
    if (str == NULL)
        return (NULL);
    str[0] = '\0';
    all->hd_data.hd_eof_len = ft_strlen(hd_eof);
    all->hd_data.str_len = 0;
    str = process_input_lines(str, hd_eof, all);
    return (str);
}

void    catch_heredoc(t_all *all)
{
    t_token *tmp;
    char    *str;
    
    tmp = all->token;
	str = NULL;
    while(tmp->next)
    {
        if (tmp->type == HEREDOC)
        {
            str = gc_strdup(append_hd(tmp->next->str, all), all);
            printf("HD_input:\n%s###############\n", str);
            // tmp->next->str = (char*)gc_realloc(all,tmp->next->str, ft_strlen(str));
            initialize_hd_data(str, all);
            handle_hd_expand(str, all);
            printf("HD_expended:%s\n", all->hd_data.new);
            tmp->next->str = gc_strdup(all->hd_data.new, all);
            // all->hd_data.new = str;
        }
        tmp = tmp->next;
    }
}