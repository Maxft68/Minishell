#include "../mandatory/minishell.h"

int	create_lexer(char *input, t_all *all)
{
	if (input && input[0] != '\0')
		add_history(input);
	if (input[0] == '\0')
		return (-1);
	if (verif_quoted(input, all) == -1)
		return (all->error_code = 2, -1);
	initialize_data(all, input);
	handle_expand(input, all);
	if (all->data.new == NULL)
		return (-1);
	all->lexer = (t_lexer *)gc_malloc(all, sizeof(t_lexer));
	all->lexer->input = gc_strdup(all->data.new, all);
	all->lexer->position = 0;
	all->lexer->c = all->lexer->input[0];
	all->lexer->cmd = true;
	all->lexer->redir = 0;
	skip_whitespace(all->lexer);
	return (0);
}

int new_tkn_char(t_token_type type, t_all *all)
{
	char	c;

	c = all->lexer->c;
	if ((type > 0 && type < 7) && !all->data.d_quote && !all->data.s_quote)
	{
		if (c == '<' || c == '>' || c == '|')
			return (1);
		if ((c == ' ' && !all->data.s_quote) && (c == ' '
				&& !all->data.d_quote))
			return (1);
	}
	return (0);
}

void	advance_char(t_lexer *lexr)
{
	lexr->position++;
	if (lexr->input[lexr->position] != '\0')
		lexr->c = lexr->input[lexr->position];
	else
		lexr->c = '\0';
}

void	skip_whitespace(t_lexer *lexr)
{
	while ((lexr->c > 9 && lexr->c < 14) || lexr->c == 32)
		advance_char(lexr);
}
