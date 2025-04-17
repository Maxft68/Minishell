/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_garbage.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdsiurds <mdsiurds@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 21:45:54 by mdsiurds          #+#    #+#             */
/*   Updated: 2025/04/13 17:54:03 by mdsiurds         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_garbage	*ft_lstnew(t_all *all, void *alloc)
{
	t_garbage	*new;

	new = malloc(sizeof(t_garbage));
	if (!new)
		ft_exit("malloc fail", all, 1);
	new->pointer = alloc;
	new->next = NULL;
	return (new);
}

void	*gc_malloc(t_all *all, size_t size)
{
	t_garbage *new;
	void *alloc;
	
	alloc = malloc(size);
	if (!alloc)
		ft_exit("malloc fail", all, 1);
	new = ft_lstnew(all, alloc);
	if (!new)
	{
		free(alloc);
		ft_exit("malloc fail", all, 1);
	}
	ft_lstadd_front(&(all->garbage), new);
	return (alloc);
}

void	free_garbage_collect(t_garbage **garbage_head)
{
	t_garbage	*garbage;
	t_garbage	*temp;
	
	if (!garbage_head || !(*garbage_head))
		return ;
	garbage = *garbage_head;
	while (garbage)
	{
		temp = garbage->next;
		if (garbage->pointer != NULL)
			free(garbage->pointer);
		free(garbage);
		garbage = temp;
	}
	*garbage_head = NULL;
}
