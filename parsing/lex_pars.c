
#include "../mandatory/minishell.h"

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
	char *new = gc_strdup(handle_expand(str, all), all);
	printf("In= %s\n",new);
	create_token(type, new, all);
}

char	*find_and_define(t_all *all, char *tmp, char *old)
{
	int i = 0;
	int j = 0;
	char *new = NULL;
	char *value = find_the_value(all, tmp);
	while (old && old[i])
		i++;
	while (value && value[j])
	{
		old[i] = value[j];
		i++;
		j++;
	}
	new = gc_strdup(old, all);
	return (new);
}

char *handle_expand(char *old, t_all *all)
{
	char *new = malloc(sizeof(char) * 4096);
	char *tmp = malloc(sizeof(char) * 4096);
	char *val = malloc(sizeof(char) * 4096);
	int i = 0;
	int j = 0;
	int t = 0;
	int x = 0;

	while(old && old[i])
	{
		if (old[i] == '$')
		{
			i++;
			t = 0;
			while(ft_isalnum(old[i]) == 1 || old[i] == '_')
				tmp[t++] = old[i++];
			tmp[t] = '\0';
			val = find_the_value(all, tmp);
			if (val)
			{
				x = 0;
				while (val[x])
					new[j++] = val[x++];
			}
			else
				new[j++] = '$';
		}
		else
			new[j++] = old[i++];
	}
	new[j] = '\0';
	free (tmp);
	return (gc_strdup(new, all));
}

// char *handle_expand(char *old, t_all *all)
// {
//     char *new = malloc(sizeof(char) * 4096);
//     int i = 0, j = 0;

//     while (old && old[i])
//     {
//         if (old[i] == '$')
//         {
//             i++;
//             int t = 0;
//             char tmp[256];
//             while (old[i] && (ft_isalnum(old[i]) || old[i] == '_') && t < 255)
//                 tmp[t++] = old[i++];
//             tmp[t] = '\0';
//             if (t > 0)
//             {
//                 char *val = find_the_value(all, tmp);
//                 if (val)
//                 {
//                     int x = 0;
//                     while (val[x])
//                         new[j++] = val[x++];
//                 }
//             }
//             // Si pas de nom de variable après le $, on garde juste le $
//             else
//                 new[j++] = '$';
//         }
//         else
//             new[j++] = old[i++];
//     }
//     new[j] = '\0';
//     return gc_strdup(new, all);
// }




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
