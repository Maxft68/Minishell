/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdsiurds <mdsiurds@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 14:03:59 by mdsiurds          #+#    #+#             */
/*   Updated: 2025/04/11 10:20:24 by mdsiurds         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_node(t_token *token)
{
	while (token)
	{
		printf("Token: %s\n", token->name);
		token = token->next;
	}
}
void	print_node_env(t_env *env)
{
	while (env)
	{
		printf("%s=", env->name);
		printf("%s\n", env->value);
		env = env->next;
	}
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

static void	ft_lstadd_back(t_token **token, t_token *new)
{
	t_token	*current;

	if (!*token)
	{
		*token = new;
		return ;
	}
	current = *token;
	while (current->next)
		current = current->next;
	current->next = new;
	return  ;
}

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
	return  ;
}

static t_token	*ft_lstnew(t_all *all, char *name)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
			ft_exit("malloc error", all, 1);
	new->name = name;
	new->next = NULL;
	return (new);
}

t_env	*ft_lstnew_env(t_all *all, char *name, char *value)
{
	t_env	*new;

	new = gc_malloc(all, sizeof(t_env));
	if (!new)
		ft_exit("malloc error", all, 1);
	new->name = name;
	new->value = value;
	new->next = NULL;
	return (new);
}

void	do_node(char **read_array, t_all *all)
{
	int		i;
	t_token	*new_node;

	i = 0;
	while (read_array && read_array[i])
	{
		new_node = ft_lstnew(all, read_array[i]);
		if (!new_node)
			ft_exit("fail", all, 0);
		ft_lstadd_back(&all->token, new_node);
		i++;
	}
	print_node(all->token); // a degager
	return ;
}

void	ft_lstclear(t_token **token)
{
	t_token	*temp;

	while (*token)
	{
		temp = (*token)->next;
		free(*token);
		*token = NULL;
		*token = temp;
	}
}
