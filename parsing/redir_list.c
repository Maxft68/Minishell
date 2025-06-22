#include "../mandatory/minishell.h"

t_token *copy_token(t_token *tokn, t_all *all)
{
	t_token	*new;

    new = NULL;
    new = (t_token*)gc_malloc(all, sizeof(t_token));
    //new = (t_token*)malloc(sizeof(t_token));
    if (!new)
        ft_exit("Cannot allocate memory10\n", all, 12);
    new->str = gc_strdup(tokn->str, all);
    //new->str = ft_strdup(tokn->str);
    new->type = tokn->type;
    new->pipe = tokn->pipe;
    new->next = NULL;
    return (new);
}

char	*search_pipe_redir(int pipe, token_type type, t_all *all)
{
    t_token *tmp;
    char    *redir;

    tmp = all->rdir_tkn;
    redir = NULL;
    while (tmp && tmp->pipe != pipe)
            tmp = tmp->next;
    if (tmp && tmp->pipe == pipe)
    {
        while (tmp->next && tmp->next->pipe == pipe)
        {
            if (tmp->type == type && tmp->next)
                redir = tmp->next->str;
            tmp = tmp->next;
        }  
    }
    return (redir);
}


void    create_redir_lst(t_all *all)
{
    t_token *tmp;

    tmp = all->token;
    while (tmp)
    {
        if (tmp->type > 7 && tmp->type < 12)
        {
            ft_tknadd_back(&all->rdir_tkn, copy_token(tmp, all));
            ft_tknadd_back(&all->rdir_tkn, copy_token(tmp->next, all));
        }
        tmp = tmp->next;
    }
}