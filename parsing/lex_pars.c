
#include "minishell.h"
// #include "../mandatory/minishell.h"

void    skip_whitespace(t_lexer *lexr)
{
    while ((lexr->c > 9 && lexr->c < 14) || lexr->c == 32)
        advance_char(lexr);
}

void create_word_token(t_all *all)
{
    int         start;
    int         len;
    char        *str;
    token_type  type;

    start = all->lexer->position;
    while (ft_isprint(all->lexer->c) && !new_tkn_char(all->lexer->c))
            advance_char(all->lexer);
    len = all->lexer->position - start;
    str = NULL;
    str = (char*)gc_malloc(all, len + 1);
    if (!str)
        ft_exit("Cannot allocate memory\n", all, 12);
    ft_strlcpy(str, all->lexer->input + start, len + 1);
    str[len] = '\0';
    if (all->lexer->first_token)
    {
        type = COMMAND;
        all->lexer->first_token = false;
    }
    else
        type = ARG;
    create_token(type, str, all);
    
}


void create_string_token(char quote, t_all *all)
{
    int         len;
    char        *str;
    token_type  type;
    
    if (quote == '"')
        type = DQ_STRING;
    else
        type = SQ_STRING;
    advance_char(all->lexer);
    int start = all->lexer->position;
    while (all->lexer->c != '\0' && all->lexer->c != quote) {
        advance_char(all->lexer);
    }
    len = all->lexer->position - start;
    str = NULL;
    str = malloc(sizeof(char)*(len + 1));
    if (!str)
        ft_exit("Cannot allocate memory\n", all, 12);
    ft_strlcpy(str, all->lexer->input + start, len + 1);
    str[len] = '\0';

    if (all->lexer->c == quote)
        advance_char(all->lexer);

    create_token(type, str, all);
}

void create_operator_token(token_type type, char *str, t_all *all)
{
    advance_char(all->lexer);
    if (type == APPEND_OUT || type == HEREDOC)
        advance_char(all->lexer);
    if (type == PIPE)
    {
        if (all->lexer->c == '|' || all->lexer->input[all->lexer->position + 1] == '|')
            ft_exit("Syntax error\n", all, 1);
        all->pipe.nb_pipe += 1;
        all->lexer->first_token = true;
    }
    if (type == VARIABLE && all->lexer->c == '$')
        ft_exit("Syntax error\n", all, 1);
    create_token(type, str, all);
}

void next_token(t_all *all)
{
    char c;
    
    skip_whitespace(all->lexer);
    c = all->lexer->c;
    //printf("Current char: %c (%d)\n", c, c);//print de test
    if (c == '|')
        create_operator_token(PIPE, "|", all);
    else if (c == '>' && all->lexer->input[all->lexer->position + 1] != '>')
        create_operator_token(REDIRECT_OUT, ">" ,all);
    else if (c == '>' && all->lexer->input[all->lexer->position + 1] == '>')
        create_operator_token(APPEND_OUT, ">>", all);
    else if (c == '<' && all->lexer->input[all->lexer->position + 1] != '<')
        create_operator_token(REDIRECT_IN, "<", all);
    else if (c == '<' && all->lexer->input[all->lexer->position + 1] == '<')
        create_operator_token(HEREDOC, "<<", all);
    else if (c == '$')
        create_operator_token(VARIABLE, "$", all);
    else if (c == 34 || c == 39)//(c == '\'' || c == '\"')
        create_string_token(c, all);
    else if (ft_isprint(c) || c == '/' || c == '-' || c == '_')
        create_word_token(all);
    else
        create_token(ILLEGAL, "", all);
}
