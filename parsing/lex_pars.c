
#include "../mandatory/minishell.h"

// void create_word_token(t_all *all)
// {
//     int         start;
//     int         len;
//     char        *str;
//     token_type  type;

//     start = all->lexer->position;
//     while (ft_isprint(all->lexer->c) && !new_tkn_char(all))
//             advance_char(all->lexer);
//     len = all->lexer->position - start;
//     str = NULL;
//     str = (char*)gc_malloc(all, len + 1);
//     if (!str)
//         ft_exit("Cannot allocate memory\n", all, 12);
//     ft_strlcpy(str, all->lexer->input + start, len + 1);
//     str[len] = '\0';
//     if (all->lexer->first_token)
//     {
//         type = COMMAND;
//         all->lexer->first_token = false;
//     }
//     else
//         type = ARG;
//     create_token(type, str, all);
    
// }

void create_word_token(t_all *all)
{
    char        *str;
    // int         s_quote;
    // int         d_quote;
    token_type  type;


    // s_quote = 0;
    // d_quote = 0;
    str = NULL;
    // str = (char*)gc_malloc(all, 1);
    str = pick_char(str, all);
    // while (ft_isprint(all->lexer->c) && !new_tkn_char(all))
    // {
    //     if (all->lexer->c == 34 && d_quote == 0 && s_quote == 0)
    //         d_quote = 1;
    //     else if (all->lexer->c == 34 && d_quote == 1 && s_quote == 0)
    //         d_quote = 0;
    //     else if (all->lexer->c == 39 && s_quote == 0 && d_quote == 0)
    //         s_quote = 1;
    //     else if (all->lexer->c == 39 && s_quote == 1 && d_quote == 0)
    //        s_quote = 0;
    //     else
    //         ft_strlcat(str, all->lexer->input + all->lexer->position, (ft_strlen(str) + 2));
    //     advance_char(all->lexer);
    // }
    // if (s_quote == 1 || d_quote == 1)
    //     ft_exit("Syntax error", all, 2);
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
    // str = NULL;
    // str = pick_char(str, all);
    advance_char(all->lexer);
    int start = all->lexer->position;
    while (all->lexer->c != '\0' && all->lexer->c != quote)
        advance_char(all->lexer);
    len = all->lexer->position - start;
    str = NULL;
    str = (char*)gc_malloc(all, len + 1);
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
        if (all->lexer->c == '|' || all->lexer->position == 1 || \
            (all->lexer->input[all->lexer->position] && \
            all->lexer->input[all->lexer->position] == '|') || \
            all->lexer->c == '\0')
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
    /* else if ((c == 34 && (all->lexer->input[all->lexer->position -1] != ' ')) \
             || (c == 39 && (all->lexer->input[all->lexer->position -1] != ' ')))*/
    else if (c == 34 || c == 39)
        create_string_token(c, all);
    else if (ft_isprint(c) || c == '/' || c == '-' || c == '_')
        create_word_token(all);
    else if (c == '\0')
        return ;
    else
        create_token(ILLEGAL, "", all);
}

void    pars_to_exec(t_all *all)
{
    while (all->lexer->c)
        next_token(all);
    if (all->token)
    {
		print_node(all->token);    //<---------------------------------------------------------printf
        list_to_tab(all);
        exec_part(all);
    }
}