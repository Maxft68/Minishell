#include "../mandatory/minishell.h"

t_token *copy_token(t_token *tokn, t_all *all)
{
    
}

void    create_redir_lst(t_all *all)
{
    t_token *tmp;

    tmp = all->token;
    while (tmp)
    {
        if (tmp->type > 5 && tmp->type < 10)
        {
            ft_tknadd_back(&all->rdir_tkn, copy_token(tmp, all));
            ft_tknadd_back(&all->rdir_tkn, copy_token(tmp->next, all));
        }
    }
}