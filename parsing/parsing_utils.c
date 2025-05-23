
#include "../mandatory/minishell.h"
#include <stddef.h>



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
char	*pick_char(char *str, t_all *all)
{
	size_t	i;

	i = 0;
    while (ft_isprint(all->lexer->c) && !new_tkn_char(all))
    {
        if (all->lexer->c == 34 && !all->lexer->d_quote && !all->lexer->s_quote)
            all->lexer->d_quote = true;
        else if (all->lexer->c == 34 && all->lexer->d_quote && !all->lexer->s_quote)
            all->lexer->d_quote = false;
        else if (all->lexer->c == 39 && !all->lexer->s_quote && !all->lexer->d_quote)
            all->lexer->s_quote = true;
        else if (all->lexer->c == 39 && all->lexer->s_quote && !all->lexer->d_quote)
           all->lexer->s_quote = false;
        else
		{
			i = ft_strlen(str);
			str = (char*)gc_realloc(all, str, i + 2);
			str[i] = all->lexer->c;
			str[i + 1] = '\0';
		}
        advance_char(all->lexer);
    }
	if (all->lexer->s_quote || all->lexer->d_quote)
        ft_exit("Syntax error", all, 2);
	return (str);
}

void   create_token(token_type type, char *str, t_all *all)
{
	t_token   *tokn;
	
	if (type == ILLEGAL)
		ft_exit("Syntax error\n", all, 2);
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
	ft_tknadd_back(&all->token, tokn);
}