#include "../mandatory/minishell.h"

char	*gc_strdup(char *s, t_all *all)
{
	char	*alloc;
	size_t	l;

	l = ft_strlen(s);
	alloc = gc_malloc(all, (l + 1) * sizeof(char));
	if (!alloc)
        ft_exit("Cannot allocate memory\n", all, 12);
    ft_strlcpy(alloc, s, l + 1);
	return (alloc);
}

void    alloc_tab_star_star(t_all *all)
{
    int     i;
    int     j;
    t_token *tmp;

    tmp = all->token;
    i = 0;
    j = 0;
    while (tmp)
    {
        if (tmp && tmp->type > 0 && tmp->type != 5)
            j++;
        if (tmp->type == PIPE || tmp->next == NULL)
        {
            all->pipe.cmd_args[i] = gc_malloc(all, (sizeof(char*) * (j + 1)));
            if (!all->pipe.cmd_args[i])
                ft_exit("Cannot allocate memory\n", all, 12);
            all->pipe.cmd_args[i][j] = NULL;
            i++;
            j = 0;
        }
        tmp = tmp->next;
    }
}

void    alloc_tab_star_star_star(t_all *all)
{
    int     i;
    t_token *tmp;

    i = 0;
    tmp = all->token;
    while (tmp)
    {
        if (tmp->type == PIPE)
            i++;
        tmp = tmp->next;
    }
    all->pipe.cmd_args = gc_malloc(all, (sizeof(char**) * (i + 2))); //si 1pipe = 2 parties
    if (!all->pipe.cmd_args)
        ft_exit("Cannot allocate memory\n", all, 12);
    all->pipe.cmd_args[i + 1] = NULL;
    alloc_tab_star_star(all);
}

void    list_to_tab(t_all *all)
{
    int     i;
    int     j;
    t_token *tmp;

    i = 0;
    j = 0;

    tmp = all->token;
    alloc_tab_star_star_star(all);
    while (tmp)
    {
        if (tmp->type == PIPE)
        {
            i++;
            j = 0;
        }
        if (tmp && tmp->type > 0 && tmp->type != 5)
        {
            // printf("%s %d %d\n", tmp->str, i , j);  <---------------------------------------------------------printf
            all->pipe.cmd_args[i][j] = NULL;
            all->pipe.cmd_args[i][j] = gc_strdup(tmp->str, all);
            // printf("pipe: %d tab %d str %s\n", i, j, tmp->str); <---------------------------------------------------------printf
            j++;
        }
        tmp = tmp->next;
    }
	// printf("\n");   <---------------------------------------------------------printf
}
