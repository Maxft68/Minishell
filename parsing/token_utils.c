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

void	syntax_error(char *str, t_all *all)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("'\n", 2);
	free_garbage_collect(&all->garbage);
}

int	check_tkn_lst(t_all *all)
{
	t_token	*tmp;
	int		i;

	i = 0;
	tmp = all->token;
	while (tmp->next)
	{
		if (tmp->type > 7 && tmp->type < 12 && tmp->next->type > 7
			&& tmp->next->type < 12)
			return (syntax_error(tmp->next->str, all), 1);
		if (tmp->type > 7 && tmp->type < 12 && tmp->next->type == 7)
			return (syntax_error(tmp->next->str, all), 1);
		if (tmp->type == 7 && tmp->next->type == 7)
			return (syntax_error(tmp->next->str, all), 1);
		if (tmp->type == 7 && i == 0)
			return (syntax_error(tmp->str, all), 1);
		tmp = tmp->next;
		i++;
	}
	if (tmp->type > 6 && tmp->type < 12)
		return (syntax_error("newline", all), 1);
	return (0);
}
