#include "lex_pars.h"


t_token   *create_token(token_type type, const char *str)
{
    t_token   *tokn;
    
    tokn = (t_token*)malloc(sizeof(t_token));
    tokn->type = type;
    tokn->str = strdup(str);
    return  (tokn);
}

void    free_token(t_token *tokn)
{
    free(tokn->str);
    free(tokn);
}

t_lexer *create_lexer(const char *input)
{
    t_lexer *lexr;

    lexr = (t_lexer*)malloc(sizeof(t_lexer));
    lexr->input = input;
    lexr->position = 0;
    lexr->c = input[0];
    lexr->first_token = true;
    return (lexr);
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