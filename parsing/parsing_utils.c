// #include "lex_pars.h"
#include "../mandatory/minishell.h"


void   create_token(token_type type, const char *str, t_all *all)
{
    t_token   *tokn;
    
    tokn = NULL;
    tokn = (t_token*)gc_malloc(all, sizeof(t_token));
    if (!tokn)
        ft_exit("Cannot allocate memory", all, 12);
    tokn->type = type;
    tokn->str = ft_strdup(str);
    // return  (tokn);
    ft_tknadd_back(&all->token, tokn);
}

// void    free_token(t_token *tokn)
// {
//     free(tokn->str);
//     free(tokn);
// }

void    create_lexer(const char *input, t_all *all)
{
    // t_lexer *lexr;

    all->lexer = (t_lexer*)gc_malloc(all, sizeof(t_lexer));
    if (!all->lexer)
        ft_exit("Cannot allocate memory", all, 12);
    all->lexer->input = input;
    all->lexer->position = 0;
    all->lexer->c = input[0];
    all->lexer->first_token = true;
    // return (lexr);
}

// void    free_lexer(t_lexer *lexr)
// {
//     free(lexr);
// }

void    advance_char(t_lexer *lexr)
{
    lexr->position++;
    if (lexr->input[lexr->position] != '\0')
        lexr->c = lexr->input[lexr->position];
    else
        lexr->c = '\0';
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

int new_tkn_char(char c)
{
    if (c == '<' || c == '>' || c == '$' || c == '|')
        return (1);
    if (c == '\'' || c == '"' || c == ' ')
        return (1);
    return (0);
}