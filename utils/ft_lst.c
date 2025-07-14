

#include "../mandatory/minishell.h"

const char	*get_t_token_type_name(t_token_type type)
{
	if (type == COMMAND)
		return ("COMMAND");
	if (type == ARG)
		return ("ARG");
	if (type == SQ_STRING)
		return ("SQ_STRING");
	if (type == DQ_STRING)
		return ("DQ_STRING");
	if (type == PIPE)
		return ("PIPE");
	if (type == REDIRECT_OUT)
		return ("REDIRECT_OUT");
	if (type == REDIRECT_IN)
		return ("REDIRECT_IN");
	if (type == APPEND_OUT)
		return ("APPEND_OUT");
	if (type == HEREDOC)
		return ("HEREDOC");
	if (type == REDIR_FILE)
		return ("REDIR_FILE");
	if (type == HD_EOF)
		return ("HD_EOF");
	if (type == ILLEGAL)
		return ("ILLEGAL");
	return ("UNKNOWN");
}

void	print_node(t_token *token)
{
	//printf("what the fuck\n");
	if (!token)
		printf("no token\n");
	if (!token->type)
		printf("not tkn type\n");
	if (!token->str)
		printf("no token str\n");
	//testerprintf("\n");
	while (token && (token->type || token->str))
	{
		//printf("Type: %u, (%s), str: %s, pipe: %d\n", token->type,get_t_token_type_name(token->type), token->str, token->pipe);
		token = token->next;
	}
	//printf("\n");
}

void	ft_lstadd_front(t_garbage **garbage, t_garbage *new)
{
	t_garbage	*second;

	if (!(*garbage))
	{
		*garbage = new;
		return ;
	}
	second = *garbage;
	new->next = second;
	*garbage = new;
	return ;
}

void	ft_lstadd_back_env(t_all *all, t_env **env, t_env *new)
{
	t_env	*current;

	if (!*env)
	{
		*env = new;
		all->env_export.nb_line_env++;
		return ;
	}
	current = *env;
	while (current->next)
		current = current->next;
	current->next = new;
	all->env_export.nb_line_env++;
	return ;
}

t_env	*ft_lstnew_env(t_all *all, char *name, char *value)
{
	t_env	*new;

	new = gc_malloc_env(all, sizeof(t_env));
	new->name = name;
	new->value = value;
	new->next = NULL;
	return (new);
}

// void	do_node(char **read_array, t_all *all)
// {
// 	int		i;
// 	t_token	*new_node;

// 	i = 0;
// 	while (read_array && read_array[i])
// 	{
// 		new_node = ft_lstnew(all, read_array[i]);
// 		if (!new_node)
// 			ft_exit("fail", all, 0);
// 		ft_lstadd_back(&all->token, new_node);
// 		i++;
// 	}
// 	// print_node(all->token); // a degager
// 	return ;
// }

void	ft_lstclear(t_token **token)
{
	t_token	*temp;

	while (*token && token)
	{
		temp = (*token)->next;
		if ((*token)->str)
		{
			free((*token)->str);
			(*token)->str = NULL;
		}
		free(*token);
		//*token = NULL;
		*token = temp;
	}
}


