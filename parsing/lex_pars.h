/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_pars.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbier <rbier@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 23:08:50 by rbier             #+#    #+#             */
/*   Updated: 2025/04/18 16:51:20 by rbier            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEX_PARS_H
# define LEX_PARS_H

//# include "../libft/libft/libft.h"
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

typedef struct  s_token
{
    token_type      type;
    char            *str;
    int             index;
    struct s_token  *next;
}               t_token;

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
char	*ft_strdup(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlen(const char *s);
int	ft_isprint(int c);
int	ft_isalnum(int c);


#endif