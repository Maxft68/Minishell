#include "minishell.h"

char    ***list_to_tab(t_all *all)
{
    int i;
    int j;

    i = 0;
    j = 0;
    alloc_tab_star_star_star(all);
    while (all->token)
    {
        if (all->token->type == PIPE)
        {
            i++;
            j = 0;
        }
        if (all->token->type < 3)
        {
            all->pipe.cmd_args[i][j] = all->token->str;
            j++;
        }//---------------------------------------------------------------ici
    }
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
        if (tmp->type < 3)
            j++;
        if (tmp->type == PIPE)
        {
            all->pipe.cmd_args[i] = gc_malloc(all, (sizeof(char*) * j + 1));
            if (!all->pipe.cmd_args[i])
                ft_exit("Cannot allocate memory", all, 12);
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
    int     j;
    t_token *tmp;

    i = 0;
    tmp = all->token;
    while (tmp)
    {
        if (tmp->type == PIPE)
            i++;
        tmp = tmp->next;
    }
    all->pipe.cmd_args = gc_malloc(all, (sizeof(char**) * (i + 2)));
    if (!all->pipe.cmd_args)
        ft_exit("Cannot allocate memory", all, 12);
    all->pipe.cmd_args[i + 1] = NULL;
    alloc_tab_star_star(all);
}
