

#include "../mandatory/minishell.h"

static t_garbage	*ft_lstnew_gc(t_all *all, void *alloc)
{
	t_garbage	*new;

	new = malloc(sizeof(t_garbage));
	if (!new)
		ft_exit("Cannot allocate memory\n", all, 12);
	new->pointer = alloc;
	new->next = NULL;
	return (new);
}

void	*gc_malloc(t_all *all, size_t size)
{
	static t_garbage	*new;
	void				*alloc;

	alloc = malloc(size);
	if (!alloc)
		ft_exit("Cannot allocate memory\n", all, 12);
	new = ft_lstnew_gc(all, alloc);
	if (!new)
	{
		free(alloc);
		ft_exit("Cannot allocate memory\n", all, 12);
	}
	ft_lstadd_front(&(all->garbage), new);
	return (alloc);
}

void	free_garbage_collect(t_garbage **garbage_head)
{
	t_garbage	*current;
	t_garbage	*next;

	if (!garbage_head || !*garbage_head)
		return ;
	current = *garbage_head;
	while (current)
	{
		next = current->next;
		if (current->pointer)
		{
			free(current->pointer);
			current->pointer = NULL;
		}
		free(current);
		current = next;
	}
	*garbage_head = NULL;
}

void	*gc_realloc(t_all *all, void *ptr, size_t size)
{
	void	*new;

	if (ptr == NULL)
	{
		ptr = gc_malloc(all, size);
		return (ptr);
	}
	new = gc_malloc(all, size);
	ft_memcpy(new, ptr, ft_strlen(ptr));
	return (new);
}
