
#include "../mandatory/minishell.h"


char	*ad_char(t_all *all, char* str)
{
	size_t	i;

	i = ft_strlen(str);
	str = (char*)gc_realloc(all, str, i + 2);
	str[i] = all->lexer->c;
	str[i + 1] = '\0';
	return (str);
}

char	*pick_char(char *str, token_type type, t_all *all)
{
	char	c;

    while (ft_isprint(all->lexer->c) && !new_tkn_char(type, all))//<---- new_tkn si en dehors quotes 
    {
		c = all->lexer->c;
        if (c == 34 && !all->lexer->d_quote && !all->lexer->s_quote)
            all->lexer->d_quote = true;
        else if (c == 34 && all->lexer->d_quote && !all->lexer->s_quote)
            all->lexer->d_quote = false;
        else if (c == 39 && !all->lexer->s_quote && !all->lexer->d_quote)
            all->lexer->s_quote = true;
        else if (c == 39 && all->lexer->s_quote && !all->lexer->d_quote)
			all->lexer->s_quote = false;
        else
			str = ad_char(all, str);
        advance_char(all->lexer);
    }
	// if (all->lexer->s_quote || all->lexer->d_quote)
    //     ft_exit("quotes Syntax error\n", all, 2);
	return (str);
}

void   create_token(token_type type, char *str, t_all *all)
{
	t_token   *tokn;
	
	if (type == ILLEGAL)
		ft_exit("Syntax error\n", all, 2);
	tokn = NULL;
	tokn = (t_token*)gc_malloc(all, sizeof(t_token));
	// tokn = (t_token*)gc_malloc(all, sizeof(t_token));
	if (!tokn)
		ft_exit("Cannot allocate memory9\n", all, 12);
	tokn->str = NULL;
	tokn->next = NULL;
	tokn->pipe = all->pipe.nb_pipe;
	tokn->type = type;
	tokn->str = gc_strdup(str, all);
	// tokn->str = gc_strdup(str, all);
	// printf("token created: ->type: %u  str: %s\n", tokn->type, tokn->str); // <--------------------------------printf
	if (!tokn->str)
		ft_exit("Cannot allocate memory10\n", all, 12);
	ft_tknadd_back(&all->token, tokn);
}
