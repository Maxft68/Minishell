

#include "../mandatory/minishell.h"

const char *get_token_type_name(token_type type)
{
    if (type == COMMAND)
        return "COMMAND";
    if (type == ARG)
        return "ARG";
    if (type == SQ_STRING)
        return "SQ_STRING";
    if (type == DQ_STRING)
        return "DQ_STRING";
    if (type == PIPE)
        return "PIPE";
    if (type == REDIRECT_OUT)
        return "REDIRECT_OUT";
    if (type == REDIRECT_IN)
        return "REDIRECT_IN";
    if (type == APPEND_OUT)
        return "APPEND_OUT";
    if (type == HEREDOC)
        return "HEREDOC";
    if (type == VARIABLE)
        return "VARIABLE";
    if (type == ILLEGAL)
        return "ILLEGAL";
    return "UNKNOWN";
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
	printf("\n");
	while (token && token->type && token->str)
	{
		printf("Type: %u, (%s), str: %s, pipe: %d\n", token->type,get_token_type_name(token->type), token->str, token->pipe);
		token = token->next;
	}
	printf("\n");
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

// static void	ft_lstadd_back(t_token **token, t_token *new)
// {
// 	t_token	*current;

// 	if (!*token)
// 	{
// 		*token = new;
// 		return ;
// 	}
// 	current = *token;
// 	while (current->next)
// 		current = current->next;
// 	current->next = new;
// 	return ;
// }

void	ft_lstadd_back_env(t_env **env, t_env *new)
{
	t_env	*current;

	if (!*env)
	{
		*env = new;
		return ;
	}
	current = *env;
	while (current->next)
		current = current->next;
	current->next = new;
	return ;
}

// static t_token	*ft_lstnew(t_all *all, char *name)
// {
// 	t_token	*new;

// 	new = NULL;
// 	new = gc_malloc(all, sizeof(t_token));
// 	if (!new)
// 		ft_exit("malloc error", all, 1);
// 	new->name = name;
// 	new->next = NULL;
// 	return (new);
// }

t_env	*ft_lstnew_env(t_all *all, char *name, char *value)
{
	t_env	*new;

	new = gc_malloc_env(all, sizeof(t_env));
	if (!new)
		ft_exit("Cannot allocate memory\n", all, 12);
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
		// *token = NULL;
		*token = temp;
	}
}
