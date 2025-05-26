

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
	void		*alloc;
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
	t_garbage	*temp;

	while (*garbage_head && garbage_head)
	{
		temp = (*garbage_head)->next;
		if ((*garbage_head)->pointer)
		{
			free((*garbage_head)->pointer);
			(*garbage_head)->pointer = NULL;
		}
		free(*garbage_head);
		*garbage_head = NULL;
		*garbage_head = temp;
	}
}

char	*gc_realloc(t_all *all, char *old, int big)
{
	int size;
	char *new;

	if (!old)
		new = gc_malloc(all, sizeof(char) * (1 + big));
	size = ft_strlen(old);
	new = gc_malloc(all, (size + 1 + big));
	ft_strlcpy(new, old, size);
	return (new);
}

// void	free_garbage_collect(t_garbage **garbage_head)
// {
// 	t_garbage	*garbage;
// 	t_garbage	*temp;

// 	if (!garbage_head || !(*garbage_head))
// 		return ;
// 	garbage = *garbage_head;
// 	while (garbage)
// 	{
// 		temp = garbage->next;
// 		if (garbage->pointer != NULL)
// 		{
// 			free(garbage->pointer);
// 			garbage->pointer = NULL;
// 		}
// 		free(garbage);
// 		garbage = NULL;
// 		garbage = temp;
// 	}
// 	*garbage_head = NULL;
// }
