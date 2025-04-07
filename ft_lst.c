/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdsiurds <mdsiurds@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 14:03:59 by mdsiurds          #+#    #+#             */
/*   Updated: 2025/04/07 17:52:56 by mdsiurds         ###   ########.fr       */
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

// static	t_token	*ft_lstadd_front(t_token **token, t_token *new)
// {
// 	t_token	*second;

// 	if (!*token)
// 	{
// 		*token = new;
// 		return (*token);
// 	}
// 	second = *token;
// 	new->next = second;
// 	*token = new;
// 	return (*token);
// }

static t_token	*ft_lstadd_back(t_token **token, t_token *new)
{
	t_token	*current;

	if (!*token)
	{
		*token = new;
		return (*token);
	}
	current = *token;
	while (current->next)
		current = current->next;
	current->next = new;
	return (*token);
}

static t_token	*ft_lstnew(char *name)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->name = name;
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
		new_node = ft_lstnew(read_array[i]);
		if (!new_node)
			ft_exit("fail", all, 0);
		ft_lstadd_back(&all->token, new_node);
		i++;
	}
	print_node(all->token);
	return ;
}

void	ft_lstclear(t_token **token)
{
	t_token	*temp;

	while (*token)
	{
		temp = (*token)->next;
		free(*token);
		*token = temp;
	}
}
