/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_pars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbier <rbier@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 16:19:52 by rbier             #+#    #+#             */
/*   Updated: 2025/04/18 17:09:12 by rbier            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex_pars.h"

void    skip_whitespace(t_lexer *lexr)
{
    while ((lexr->c > 9 && lexr->c < 14) || lexr->c == 32)
        advance_char(lexr);
}

t_token *create_word_token(t_lexer *lexr)
{
    int         start;
    int         len;
    char        *str;
    token_type  type;
    t_token     *tokn;

    start = lexr->position;
    while (ft_isprint(lexr->c) && lexr->c != ' ')// || lexr->c == '/' || lexr->c == '-')
            advance_char(lexr);
    len = lexr->position - start;
    str = (char*)malloc(len + 1);
    ft_strlcpy(str, lexr->input + start, len + 1);
    str[len] = '\0';
    if (lexr->first_token)
    {
        type = COMMAND;
        lexr->first_token = false;
    }
    else
        type = ARG;
    tokn = create_token(type, str);
    return (tokn);
    
}


t_token *create_string_token(t_lexer*lexr, char quote)
{
    int     len;
    char    *str;
    advance_char(lexr);
    int start = lexr->position;
    while (lexr->c != '\0' && lexr->c != quote) {
        advance_char(lexr);
    }
    len = lexr->position - start;
    str = (char*)malloc(len + 1);
    ft_strlcpy(str, lexr->input + start, len + 1);
    str[len] = '\0';

    if (lexr->c == quote) {
        advance_char(lexr);
    }

    return create_token(STRING, str);
}

t_token *create_operator_token(t_lexer *lexr, token_type type, const char *str)
{
    advance_char(lexr);
    if (type == APPEND_OUT || type == HEREDOC)
        advance_char(lexr);
    return (create_token(type, str));
}

t_token *next_token(t_lexer *lexr)
{
    skip_whitespace(lexr);
    if (lexr->c == '|')
        return (create_operator_token(lexr, PIPE, "|"));
    else if (lexr->c == '>' && lexr->input[lexr->position + 1] != '>')
        return (create_operator_token(lexr, REDIRECT_OUT, ">"));
    else if (lexr->c == '>' && lexr->input[lexr->position + 1] == '>')
        return (create_operator_token(lexr, APPEND_OUT, ">>"));
    else if (lexr->c == '<' && lexr->input[lexr->position + 1] != '<')
        return (create_operator_token(lexr, REDIRECT_IN, "<"));
    else if (lexr->c == '<' && lexr->input[lexr->position + 1] == '<')
        return (create_operator_token(lexr, HEREDOC, "<<"));
    else if (lexr->c == '$')
        return (create_operator_token(lexr, VARIABLE, "$"));
    else if (lexr->c == '\'' || lexr->c == '\"')
        return (create_string_token(lexr, lexr->c));
    else if (ft_isprint(lexr->c) || lexr->c == '/' \
            || lexr->c == '-' || lexr->c == '_')
        return (create_word_token(lexr));
    else
        return (create_token(ILLEGAL, ""));
}
