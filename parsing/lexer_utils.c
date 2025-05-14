#include "../mandatory/minishell.h"

void    create_lexer(char *input, t_all *all)
{
    all->lexer = (t_lexer*)gc_malloc(all, sizeof(t_lexer));
    if (!all->lexer)
        ft_exit("Cannot allocate memory\n", all, 12);
    all->lexer->input = gc_strdup(input, all);
    free(input);
    all->lexer->position = 0;
    all->lexer->c = all->lexer->input[0];
    all->lexer->first_token = true;
    skip_whitespace(all->lexer);
}

int new_tkn_char(char c)
{
    if (c == '<' || c == '>' || c == '$' || c == '|')
        return (1);
    if (c == '\'' || c == '"' || c == ' ')
        return (1);
    return (0);
}

void    advance_char(t_lexer *lexr)
{
    lexr->position++;
    if (lexr->input[lexr->position] != '\0')
        lexr->c = lexr->input[lexr->position];
    else
        lexr->c = '\0';
}

void    skip_whitespace(t_lexer *lexr)
{
    while ((lexr->c > 9 && lexr->c < 14) || lexr->c == 32)
        advance_char(lexr);
}