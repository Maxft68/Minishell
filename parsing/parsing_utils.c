// #include "lex_pars.h"
#include "./mandatory/minishell.h"


t_token   *create_token(token_type type, const char *str, t_all *all)
{
    t_token   *tokn;
    
    tokn = (t_token*)malloc(sizeof(t_token));
    tokn->type = type;
    tokn->str = ft_strdup(str);
    return  (tokn);
}

void    free_token(t_token *tokn)
{
    free(tokn->str);
    free(tokn);
}

void    create_lexer(const char *input, t_all *all)
{
    // t_lexer *lexr;

    all->lexer = (t_lexer*)malloc(sizeof(t_lexer));
    all->lexer->input = input;
    all->lexer->position = 0;
    all->lexer->c = input[0];
    all->lexer->first_token = true;
    // return (lexr);
}

void    free_lexer(t_lexer *lexr)
{
    free(lexr);
}

void    advance_char(t_lexer *lexr)
{
    lexr->position++;
    if (lexr->input[lexr->position] != '\0')
        lexr->c = lexr->input[lexr->position];
    else
        lexr->c = '\0';
}