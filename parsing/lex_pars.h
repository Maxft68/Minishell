/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_pars.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbier <rbier@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 23:08:50 by rbier             #+#    #+#             */
/*   Updated: 2025/04/16 23:15:59 by rbier            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEX_PARS_H
# define LEX_PARS_H

# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <ctype.h> //pour fonctions isalnum, isdigit, isspace, etc...

typedef enum
{
    COMMAND,
    ARG,
    PIPE,
    REDIRECT_OUT,
    REDIRECT_IN,
    APPEND_OUT,
    HEREDOC,
    VARIABLE,
    STRING,
    ILLEGAL,
}       token_type;

typedef struct s_token
{
    token_type  type;
    char        *str;
}       t_token;

typedef struct s_lexer
{
    const char  *input;
    int         position;
    char        c;
    bool        first_token;
}       t_lexer;

t_token *create_token(token_type type, const char *str);
void    free_token(t_token *tokn);
t_lexer *create_lexer(const char *input);
void    free_lexer(t_lexer *lexr);
t_token *next_token(t_lexer *lexr);
void    advance_char(t_lexer *lexr);


#endif