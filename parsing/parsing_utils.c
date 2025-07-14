
#include "../mandatory/minishell.h"

char	*ad_char(t_all *all, char c, char *str)
{
	size_t	i;

	i = ft_strlen(str);
	str = (char *)gc_realloc(all, str, i + 2);
	str[i] = c;
	str[i + 1] = '\0';
	return (str);
}

char	*pick_char(char *str, t_token_type type, t_all *all)
{
	char	c;

	reset_quotes(all);
	while (ft_isprint(all->lexer->c) && !new_tkn_char(type, all))
	{
		c = all->lexer->c;
		if (c == 34 || c == 39)
			check_quotes(c, all);
		if ((c != 34 && c != 39) || (c == 34 && all->data.s_quote) || (c == 39
				&& all->data.d_quote))
			str = ad_char(all, c, str);
		advance_char(all->lexer);
	}
	return (str);
}

void	create_token(t_token_type type, char *str, t_all *all)
{
	t_token	*tokn;

	if (type == ILLEGAL)
		ft_exit("Syntax error\n", all, 2);
	tokn = NULL;
	tokn = (t_token *)gc_malloc(all, sizeof(t_token));
	tokn->str = NULL;
	tokn->next = NULL;
	tokn->pipe = all->pipe.nb_pipe;
	tokn->type = type;
	tokn->str = gc_strdup(str, all);
	ft_tknadd_back(&all->token, tokn);
}
