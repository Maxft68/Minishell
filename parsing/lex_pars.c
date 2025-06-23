
#include "../mandatory/minishell.h"

token_type	def_redir(t_all *all)
{
	token_type	type;

	if (all->lexer->redir == 2)
		type = HD_EOF;
	else
		type = REDIR_FILE;
	all->lexer->redir = 0;
	return (type);
}

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
		else if (all->lexer->redir)// && !all->lexer->cmd)
			type = def_redir(all);
		else
			type = ARG;
		// all->lexer->cmd = true;
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

// int	check_tkn_lst(t_all *all)
// {
// 	t_token	*tmp;

// 	tmp = all->token;
// 	while (tmp)
// 	{
// 		if (tmp->type > 5 && tmp->type < 10 && 
// 			tmp->next->type > 4 && tmp->next->type < 10)
// 		if (tmp->type > 5 && tmp->type < 10 && tmp->next->type > 4 && tmp->next->type < 10)
// 		{
// 			write(2, "tash: syntax error near unexpected token `", 42);
// 			write(2, tmp->next->str, ft_strlen(tmp->next->str));
// 			write(2, "'\n", 2);
// 			free_garbage_collect(&all->garbage);
// 			ft_lstclear(&all->token);
// 			return (1);
// 			// ft_exit(NULL, all, 1);
// 		}
// 		tmp = tmp->next;
// 	}
// 	return (0);
// }

int    pars_to_exec(t_all *all)
{
	while (all->lexer->c)
		next_token(all);
	//print_node(all->token);    //<---------------------------------------------------------printf
	if (all->token && !check_tkn_lst(all))
	{
		catch_heredoc(all);
		create_redir_lst(all);
		//print_node(all->rdir_tkn);
		list_to_tab(all);
		printf("in/out: %s\n", search_pipe_redir(1, 6, all)); //<--------------------------------printf
		printf("input: %s\n", all->lexer->input);
		if (exec_part(all) == 1)
			return(1);
	}
	return(0);
}
