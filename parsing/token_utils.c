#include "../mandatory/minishell.h"

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

void    syntax_error(char *str, t_all *all)
{
    ft_putstr_fd("WriteOneMe: syntax error near unexpected token `", 2);
    ft_putstr_fd(str, 2);
    ft_putstr_fd("'\n", 2);
    free_garbage_collect(&all->garbage);
	ft_lstclear(&all->token);
}   

int check_tkn_lst(t_all *all)
{
	t_token *tmp;
    int     i;

    i = 0;
	tmp = all->token;
	while (tmp->next)
	{
		if (tmp->type > 5 && tmp->type < 10 && \
			tmp->next->type > 4 && tmp->next->type < 10)
			return (syntax_error(tmp->next->str, all), 1);
        if (tmp->type == 5 && i == 0)
            return (syntax_error(tmp->str, all), 1);
		tmp = tmp->next;
        i++;
	}
    if (tmp->type > 4 && tmp->type < 10)
        return (syntax_error("newline", all), 1);
    return (0);
}
