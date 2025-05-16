
#include "../mandatory/minishell.h"


void   create_token(token_type type, char *str, t_all *all)
{
    t_token   *tokn;
    
    if (type == ILLEGAL)
        ft_exit("Syntax error\n", all, 1);
    tokn = NULL;
    tokn = (t_token*)malloc(sizeof(t_token));
    // tokn = (t_token*)gc_malloc(all, sizeof(t_token));
    if (!tokn)
        ft_exit("Cannot allocate memory\n", all, 12);
    tokn->str = NULL;
    tokn->next = NULL;
    tokn->pipe = all->pipe.nb_pipe;
    tokn->type = type;
    tokn->str = ft_strdup(str);
    // tokn->str = gc_strdup(str, all);
	// printf("token created: ->type: %u  str: %s\n", tokn->type, tokn->str); // <--------------------------------printf
    if (!tokn->str)
		ft_exit("Cannot allocate memory\n", all, 12);
	// if (type > 5 && type < 10)
	// 	ft_tknadd_back(&all->rdir_tkn, tokn);//creer une fonction de copie de token pour ajouter à *rdir_tkn
    ft_tknadd_back(&all->token, tokn);
}

void	ft_tknadd_back(t_token **lst, t_token *tkn)
{
	t_token	*tmp;

	if (*lst == NULL)
	{
		*lst = tkn;
		return ;
	}
	if (*lst != NULL)
	{
		tmp = ft_tknlast(*lst);
		tmp->next = tkn;
        // tkn->prev = tmp;
	}
}

t_token	*ft_tknlast(t_token *lst)
{
	t_token	*tmp;

	if (lst == NULL)
		return (NULL);
	tmp = lst;
	while (tmp->next != NULL)
		tmp = tmp->next;
	return (tmp);
}
