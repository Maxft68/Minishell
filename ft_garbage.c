/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_garbage.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdsiurds <mdsiurds@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 21:45:54 by mdsiurds          #+#    #+#             */
/*   Updated: 2025/04/07 22:00:54 by mdsiurds         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*gc_malloc(t_all *all, size_t size)
{
	void *alloc;
	alloc = malloc(size);
	if (!alloc)
		ft_exit("gc_malloc fail", all, 1);
	ft_lstadd_front(&all->garbage, alloc);
	return (alloc);
}

void	free_garbage_collect(t_all *all)
{
	t_garbage	*temp;
	
	if (!all->garbage)
		return ;
	temp = all->garbage;
	while (temp->next)
	{
		temp = temp->next;
		free(all->temp->pointer);
		free(all->temp); // pas sur
	}
	free(all->temp->pointer);
	free(all->temp); // pas sur
}
