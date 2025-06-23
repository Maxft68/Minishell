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

char *append_hd(char *hd_eof, t_all *all)
{
    char *str;
    char *line;

    str = gc_malloc(all, sizeof(char) * 1);
    str[0] = '\0';
    all->hd_data.hd_eof_len = ft_strlen(hd_eof);
    all->hd_data.str_len = 0;
    while (1)
    {
        line = readline("heredoc:");
        if (line == NULL)
            break;
        if (ft_strncmp(line, hd_eof, all->hd_data.hd_eof_len) == 0 &&
            ft_strlen(line) == all->hd_data.hd_eof_len)
            break;
        if (line != NULL)
        {
            char *new_str = append_line(str, line, all);
            if (new_str == NULL)
                break;
            str = new_str;
            free(line);
        }
    }
	if (line)
		free(line);
    if (str != NULL && all->hd_data.str_len > 0)
        str[all->hd_data.str_len - 1] = '\0';
    return (str);
}

// char	*append_hd(char* hd_eof, t_all *all)
// {
// 	char	*str;
// 	char	*line;
// 	size_t	len;

// 	// str = ft_strdup("");
// 	// str = NULL;
// 	str = gc_malloc(all, sizeof(char) * 1);
//     if (str != NULL)
// 		str[0] = '\0';
// 	line = NULL;
// 	len = 0;
// 	while (1)
// 	{
// 		line = ft_strdup(readline("heredoc:"));
// 		if (ft_strncmp(line, hd_eof, ft_strlen(hd_eof)) == 0)
// 		{
// 			free(line);
// 			break;
// 		}
// 		if (line != NULL)
// 		{
// 			len = (ft_strlen(str) + ft_strlen(line));
//         // printf("len = %zu\n", len);
// 			str = (char*)gc_realloc(all, str, (len + 2));
// 			if (str == NULL)
// 			{
// 				free(line);
// 				break;
// 			}
// 			ft_strlcat(str, line, len + 2);
// 			ft_strlcat(str, "\n", len + 2);//(ft_strlen(str) + 2));
// 			free(line);
// 		}
// 	}
// 	if (str != NULL && ft_strlen(str) > 0)
// 		str[ft_strlen(str) - 1] = '\0';
// 	return (str);
// }

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
            printf("HD_input:\n%s\n###############\n", str);
            // tmp->next->str = (char*)gc_realloc(all,tmp->next->str, ft_strlen(str));
            tmp->next->str = gc_strdup(str, all);
            all->hd_data.new = str;
        }
        tmp = tmp->next;
    }
}