
#include "../mandatory/minishell.h"
#include <string.h>

t_token_type	def_redir(t_all *all)
{
	t_token_type	type;

	if (all->lexer->redir == 2)
		type = HD_EOF;
	else
		type = REDIR_FILE;
	all->lexer->redir = 0;
	return (type);
}

void	create_word_token(t_all *all)
{
	char			*str;
	t_token_type	type;

	if (all->lexer->cmd && !all->lexer->redir)
	{
		type = COMMAND;
		all->lexer->cmd = false;
	}
	else
	{
		if (all->lexer->c == 34)
			type = DQ_STRING;
		else if (all->lexer->c == 39)
			type = SQ_STRING;
		else if (all->lexer->redir)
			type = def_redir(all);
		else
			type = ARG;
	}
	str = NULL;
	str = pick_char(str, type, all);
	if (str == NULL)
		str = gc_strdup("", all);
	create_token(type, str, all);
}

void	create_operator_token(t_token_type type, char *str, t_all *all)
{
	advance_char(all->lexer);
	if (type == PIPE)
	{
		all->pipe.nb_pipe += 1;
		all->lexer->cmd = true;
		all->lexer->redir = 0;
	}
	else
	{
		if (type == APPEND_OUT || type == HEREDOC)
			advance_char(all->lexer);
		if (type == HEREDOC)
			all->lexer->redir = 2;
		else
			all->lexer->redir = 1;
	}
	create_token(type, str, all);
}

void	next_token(t_all *all)
{
	char	c;

	skip_whitespace(all->lexer);
	c = all->lexer->c;
	if (c == '|')
		create_operator_token(PIPE, "|", all);
	else if (c == '>' && all->lexer->input[all->lexer->position + 1] != '>')
		create_operator_token(REDIRECT_OUT, ">", all);
	else if (c == '>' && all->lexer->input[all->lexer->position + 1] == '>')
		create_operator_token(APPEND_OUT, ">>", all);
	else if (c == '<' && all->lexer->input[all->lexer->position + 1] != '<')
		create_operator_token(REDIRECT_IN, "<", all);
	else if (c == '<' && all->lexer->input[all->lexer->position + 1] == '<')
		create_operator_token(HEREDOC, "<<", all);
	else if (ft_isprint(c) || c == '/' || c == '-' || c == '_')
		create_word_token(all);
	else if (c == '\0' && !all->lexer->input[all->lexer->position + 1])
		return ;
	else
		create_token(ILLEGAL, "", all);
}

int	pars_to_exec(t_all *all)
{
	while (all->lexer->c)
		next_token(all);
	if (all->token && !check_tkn_lst(all))
	{
		catch_heredoc(all);
		if (g_sigint_flag == 1)
		{
			g_sigint_flag = 0;
			return (1);
		}
		create_redir_lst(all);
		list_to_tab(all);
		if (exec_part(all) == 1)
			return (1);
	}
	return (0);
}
