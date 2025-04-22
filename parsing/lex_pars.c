/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_pars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbier <rbier@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 16:19:52 by rbier             #+#    #+#             */
/*   Updated: 2025/04/22 16:12:44 by rbier            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "lex_pars.h"
#include "minishell.h"

void    skip_whitespace(t_lexer *lexr)
{
    while ((lexr->c > 9 && lexr->c < 14) || lexr->c == 32)
        advance_char(lexr);
}

t_token *create_word_token(t_all *all)
{
    int         start;
    int         len;
    char        *str;
    token_type  type;
    t_token     *tokn;

    start = all->lexer->position;
    while (ft_isprint(all->lexer->c) && all->lexer->c != ' ')
            advance_char(all->lexer);
    len = all->lexer->position - start;
    str = (char*)malloc(len + 1);
    ft_strlcpy(str, all->lexer->input + start, len + 1);
    str[len] = '\0';
    if (all->lexer->first_token)
    {
        type = COMMAND;
        all->lexer->first_token = false;
    }
    else
        type = ARG;
    tokn = create_token(type, str, all);
    return (tokn);
    
}


t_token *create_string_token(char quote, t_all *all)
{
    int     len;
    char    *str;
    advance_char(all->lexer);
    int start = all->lexer->position;
    while (all->lexer->c != '\0' && all->lexer->c != quote) {
        advance_char(all->lexer);
    }
    len = all->lexer->position - start;
    str = (char*)malloc(len + 1);
    ft_strlcpy(str, all->lexer->input + start, len + 1);
    str[len] = '\0';

    if (all->lexer->c == quote)
        advance_char(all->lexer);

    return create_token(STRING, str, all);
}

t_token *create_operator_token(token_type type, const char *str, t_all *all)
{
    advance_char(all->lexer);
    if (type == APPEND_OUT || type == HEREDOC)
        advance_char(all->lexer);
    return (create_token(type, str, all));
}

t_token *next_token(t_all *all)
{
    char c;
    
    c = all->lexer->c;
    skip_whitespace(all->lexer);
    if (c == '|')
        return (create_operator_token(PIPE, "|", all));
    else if (c == '>' && all->lexer->input[all->lexer->position + 1] != '>')
        return (create_operator_token(REDIRECT_OUT, ">" ,all));
    else if (c == '>' && all->lexer->input[all->lexer->position + 1] == '>')
        return (create_operator_token(APPEND_OUT, ">>", all));
    else if (c == '<' && all->lexer->input[all->lexer->position + 1] != '<')
        return (create_operator_token(REDIRECT_IN, "<", all));
    else if (c == '<' && all->lexer->input[all->lexer->position + 1] == '<')
        return (create_operator_token(HEREDOC, "<<", all));
    else if (c == '$')
        return (create_operator_token(VARIABLE, "$", all));
    else if (c == '\'' || c == '\"')
        return (create_string_token(c, all));
    else if (ft_isprint(c) || c == '/' \
            || c == '-' || c == '_')
        return (create_word_token(all));
    else
        return (create_token(ILLEGAL, "", all));
}
