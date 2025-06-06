
#include "../mandatory/minishell.h"

void	initialize_data(t_all *all, char *old)
{
	all->data.z = 0;
	all->data.j = 0;
	all->data.new = NULL;
	all->data.tmp = gc_malloc(all, sizeof(old));

}
void	part_one(t_all *all, char *old, char *val)
{
	all->data.z++;
	all->data.t = 0;

	if ((ft_isdigit(old[all->data.z]) || !ft_isalpha(old[all->data.z]))
		&& old[all->data.z] != '_')
	{
		if (old[all->data.z] != 39)
			all->data.z++;
		return;
	}
	while(ft_isalnum(old[all->data.z]) == 1 || old[all->data.z] == '_')
		all->data.tmp[all->data.t++] = old[all->data.z++];
	all->data.tmp[all->data.t] = '\0';
	val = find_the_value(all, all->data.tmp);
	if (val && all->data.t > 0)
	{
		if (!all->data.new)
			all->data.new = gc_strdup(val, all);
		else
		{
			all->data.temp = gc_strjoin(all, all->data.new, val);
			all->data.new = all->data.temp;
		}
	}
}

void	part_two(t_all *all, char *old)
{
	char tmp[2];
	tmp[0] = old[all->data.z];
	tmp[1] = '\0';
	if (!all->data.new)
		all->data.new = gc_strdup(tmp, all);
	else
	{
		all->data.temp = gc_strjoin(all, all->data.new, tmp);
		all->data.new = all->data.temp;
	}
	all->data.z++;
}

void	handle_expand(char *old, t_all *all)
{
	char *val;
	bool d_quote = false;
	bool s_quote = false;
	val = NULL;
	while(old && old[all->data.z])
	{
        if (old[all->data.z] == 34 && !d_quote && !s_quote)
            d_quote = true;
        else if (old[all->data.z] == 34 && d_quote && !s_quote)
            d_quote = false;
        else if (old[all->data.z] == 39 && !s_quote && !d_quote)
            s_quote = true;
        else if (old[all->data.z] == 39 && s_quote && !d_quote)
			s_quote = false;
		if (old[all->data.z] == '$' && 
			(old[all->data.z + 1] != ' ' && old[all->data.z + 1]) && !s_quote)
		{
			part_one(all, old, val);
			d_quote = false;
			s_quote = false;
		}
		else
			part_two(all, old);
	}
}

// void	part_one(t_all *all, char *old, char *val)
// {
// 	all->data.z++;
// 	all->data.t = 0;
// 	while(ft_isalnum(old[all->data.z]) == 1 || old[all->data.z] == '_')
// 		all->data.tmp[all->data.t++] = old[all->data.z++];
// 	all->data.tmp[all->data.t] = '\0';
// 	val = find_the_value(all, all->data.tmp);
// 	if (val && all->data.t > 0)
// 	{
// 		if (!all->data.new)
// 			all->data.new = gc_strdup(val, all);
// 		else
// 		{
// 			all->data.temp = gc_strjoin(all, all->data.new, val);
// 			all->data.new = all->data.temp;
// 		}
// 	}
// }

// void	part_two(t_all *all, char *old)
// {
// 	char tmp[2];
// 	tmp[0] = old[all->data.z];
// 	tmp[1] = '\0';
// 	if (!all->data.new)
// 		all->data.new = gc_strdup(tmp, all);
// 	else
// 	{
// 		all->data.temp = gc_strjoin(all, all->data.new, tmp);
// 		all->data.new = all->data.temp;
// 	}
// 	all->data.z++;
// }

// void	handle_expand(char *old, t_all *all)
// {
// 	char *val;

// 	val = NULL;
// 	while(old && old[all->data.z])
// 	{
// 		if (old[all->data.z] == '$' && old[all->data.z + 1])
// 		{
// 			part_one(all, old, val);
// 		}
// 		else
// 		{
// 			part_two(all, old);
// 		}
// 	}
// }

void create_word_token(t_all *all)
{
	char        *str;
	token_type  type;

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
		else if (all->lexer->redir && !all->lexer->cmd)
			type = REDIR_FILE;
		else
			type = ARG;
		all->lexer->cmd = true;
	}
	str = NULL;
	// initialize_data(all, str);
	// handle_expand(str, all);
	str = pick_char(str, type, all);
	create_token(type, str, all);
}


void create_operator_token(token_type type, char *str, t_all *all)
{
	advance_char(all->lexer);
	// if (type == APPEND_OUT || type == HEREDOC)
	// 	advance_char(all->lexer);
	if (type == PIPE)
	{
		if (all->lexer->c == '|' || all->lexer->position == 1 || \
			(all->lexer->input[all->lexer->position] && \
			all->lexer->input[all->lexer->position] == '|') || \
			all->lexer->c == '\0')
			ft_exit("Syntax error\n", all, 1);
		all->pipe.nb_pipe += 1;
		all->lexer->cmd = true;
	}
	else
	{
		if (type == APPEND_OUT || type == HEREDOC)
			advance_char(all->lexer);
		all->lexer->cmd = false;
		all->lexer->redir = true;
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
		create_redir_lst(all);
		print_node(all->token);    //<---------------------------------------------------------printf
		// print_node(all->rdir_tkn);
		list_to_tab(all);
		printf("in/out: %s\n", search_pipe_redir(1, 7, all)); //<--------------------------------printf
		exec_part(all);
	}
}
