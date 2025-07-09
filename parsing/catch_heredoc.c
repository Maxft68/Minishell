#include "../mandatory/minishell.h"
#include <signal.h>

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

// bool    escape_hd(char *line)
// {
//     // g_sigint_flag = 0;
//     free(line);
//     return (true);
// }

static void	sigint_hd(int signum)
{
	if (signum == SIGINT)
	{
		g_sigint_flag = 1;
		ft_putstr_fd("\n", STDOUT_FILENO);
		close(STDIN_FILENO);
        return;
	}
}

static char *process_input_lines(char *str, char *hd_eof, t_all *all)
{
    char *line;
    char *new_str;

    while (1)
    {
        signal(SIGINT, &sigint_hd);
        // if (g_sigint_flag == 1)// && escape_hd(line))
        // {
        //     printf("premier_catch");
        //     g_sigint_flag = 0; // Réinitialise le flag
        //     break; // Quitte la boucle si Ctrl-C est pressé
        // }
        line = readline("> ");
        if (line == NULL)
            break;
        // if (g_sigint_flag == 1)// && escape_hd(line))
        // {
        //     printf("deuxieme_catch\n");
        //     g_sigint_flag = 0; // Réinitialise le flag
        //     if (line)
        //         free(line);
        //     // close(STDIN_FILENO);
        //     return (NULL);
        //     // break; // Quitte la boucle si Ctrl-C est pressé
        // }
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
    // if (line != NULL)
    //     free(line);
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
            //testerprintf("HD_input:\n%s###############\n", str);
            // tmp->next->str = (char*)gc_realloc(all,tmp->next->str, ft_strlen(str));
            initialize_hd_data(str, all);
            if (g_sigint_flag == 1)
            {
                str = NULL;
                tmp->next->str = NULL;
            }
            if (!str)
            {
                kill(0, 2);
                return;
            }
            if (str != NULL)
                handle_hd_expand(str, all);
            //testerprintf("HD_expended:%s\n", all->hd_data.new);
            tmp->next->str = gc_strdup(all->hd_data.new, all);
            // all->hd_data.new = str;
        }
        tmp = tmp->next;
    }
}