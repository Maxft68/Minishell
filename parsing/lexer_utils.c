#include "../mandatory/minishell.h"

int	verif_quoted(char *input)
{

	int i;
	int c;
	bool d_quote = false;
	bool s_quote = false;
	i = 0;
	while(input[i])
	{
		c = input[i];
        if (c == 34 && !d_quote && !s_quote)
            d_quote = true;
        else if (c == 34 && d_quote && !s_quote)
            d_quote = false;
        else if (c == 39 && !s_quote && !d_quote)
            s_quote = true;
        else if (c == 39 && s_quote && !d_quote)
			s_quote = false;
		i++;
	}
	if (s_quote || d_quote)
	{
		ft_putstr_fd("Quotes Syntax error\n", 2);
		return(-1);
	}
	return (0);
}

int	create_lexer(char *input, t_all *all)
{
	if (!input)
		ft_exit("exit\n", all, 0);
    if (input && input[0] != '\0')
		add_history(input);
    if (input[0] == '\0')
		return (-1);
	if (verif_quoted(input) == -1)
		return (-1);
	initialize_data(all, input);
	handle_expand(input, all);
    all->lexer = (t_lexer*)gc_malloc(all, sizeof(t_lexer));
    all->lexer->input = gc_strdup(all->data.new, all);
    free(input);
    all->lexer->position = 0;
    all->lexer->c = all->lexer->input[0];
    all->lexer->s_quote = false;
    all->lexer->d_quote = false;
    all->lexer->first_token = true;
    skip_whitespace(all->lexer);
	return (0);
}

int new_tkn_char(t_all *all)
{
    char    c;

    c = all->lexer->c;
    if (c == '<' || c == '>' || c == '|')// || c == '$' )
        return (1);
    if ((c == ' ' && !all->lexer->s_quote) && (c == ' ' && !all->lexer->d_quote))
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