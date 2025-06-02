
#include "../mandatory/minishell.h"

void	initialize_data(t_all *all)
{
	all->data.z = 0;
	all->data.j = 0;
	all->data.new = gc_malloc(all, sizeof(char) * 4096);
	all->data.tmp = gc_malloc(all, sizeof(char) * 4096);
}

void create_word_token(t_all *all)
{
	char        *str;
	token_type  type;

	if (all->lexer->first_token)
	{
		type = COMMAND;
		all->lexer->first_token = false;
	}
	else
	{
		if (all->lexer->c == 34)
			type = DQ_STRING;
		else if (all->lexer->c == 39)
			type = SQ_STRING;
		else
			type = ARG;
	}
	str = NULL;
	str = pick_char(str, all);
	initialize_data(all);
	char *new = gc_strdup(handle_expand(str, all), all);
	create_token(type, new, all);
}

char *handle_expand(char *old, t_all *all)
{
	char *val;

	while(old && old[all->data.z])
	{
		if (old[all->data.z] == '$' && old[all->data.z + 1])
		{
			all->data.z++;
			all->data.t = 0;
			while(ft_isalnum(old[all->data.z]) == 1 || old[all->data.z] == '_')
				all->data.tmp[all->data.t++] = old[all->data.z++];
			all->data.tmp[all->data.t] = '\0';
			val = find_the_value(all, all->data.tmp);
			if (val && all->data.t > 0)
			{
				all->data.x = 0;
				while (val[all->data.x])
					all->data.new[all->data.j++] = val[all->data.x++];
			}
		}
		else
			all->data.new[all->data.j++] = old[all->data.z++];
	}
	all->data.new[all->data.j] = '\0';
	return (free(all->data.tmp), gc_strdup(all->data.new, all));
}


// void create_string_token(char quote, t_all *all)
// {
//     int         len;
//     char        *str;
//     token_type  type;
	
//     if (quote == '"')
//         type = DQ_STRING;
//     else
//         type = SQ_STRING;
//     // str = NULL;
//     // str = pick_char(str, all);
//     advance_char(all->lexer);
//     int start = all->lexer->position;
//     while (all->lexer->c != '\0' && all->lexer->c != quote)
//         advance_char(all->lexer);
//     len = all->lexer->position - start;
//     str = NULL;
//     str = (char*)gc_malloc(all, len + 1);
//     if (!str)
//         ft_exit("Cannot allocate memory\n", all, 12);
//     ft_strlcpy(str, all->lexer->input + start, len + 1);
//     str[len] = '\0';
//     if (all->lexer->c == quote)
//         advance_char(all->lexer);
//     create_token(type, str, all);
// }

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
	// if (type == VARIABLE && all->lexer->c == '$') //<---------------------------- à déplacer dans pick_char
	//     ft_exit("Syntax error\n", all, 1);
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
	// else if (c == '$')
	//     create_operator_token(VARIABLE, "$", all);
	/* else if ((c == 34 && (all->lexer->input[all->lexer->position -1] != ' ')) \
			|| (c == 39 && (all->lexer->input[all->lexer->position -1] != ' ')))*/
	// else if (c == 34 || c == 39)
	//     create_string_token(c, all);
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
