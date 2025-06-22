

#include "../mandatory/minishell.h"

static t_garbage	*ft_lstnew_gc(t_all *all, void *alloc)
{
	t_garbage	*new;

	new = malloc(sizeof(t_garbage));
	if (!new)
		ft_exit("Cannot allocate memory15\n", all, 12);
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
		ft_exit("Cannot allocate memory16\n", all, 12);
	new = ft_lstnew_gc(all, alloc);
	if (!new)
	{
		free(alloc);
		ft_exit("Cannot allocate memory17\n", all, 12);
	}
	ft_lstadd_front(&(all->garbage), new);
	return (alloc);
}

void	free_garbage_collect(t_garbage **garbage_head)
{
    t_garbage	*current;
    t_garbage	*next;

    if (!garbage_head || !*garbage_head)
        return;
    current = *garbage_head;
    while (current)
    {
        next = current->next;         // 1. Sauvegarder le nœud suivant
        if (current->pointer)
            free(current->pointer);   // 2. Libérer la mémoire allouée
        free(current);                // 3. Libérer le nœud de la liste lui-même
        current = next;               // 4. Passer au nœud suivant
    }
    *garbage_head = NULL;             // 5. Réinitialiser la tête de liste
}

// void	free_garbage_collect(t_garbage **garbage_head)
// {
// 	t_garbage	*current;
// 	t_garbage	*next;

// 	if (!garbage_head)
// 		return;
// 	current = *garbage_head;
// 	while (current)
// 	{
// 		next = current->next;
// 		if (current->pointer)
// 			free(current->pointer);
// 		free(current);
// 		current = next;
// 	}
// 	*garbage_head = NULL;
// }

// void	free_garbage_collect(t_garbage **garbage_head)
// {
// 	t_garbage	*current;
// 	t_garbage	*next;

// 	if (!garbage_head)
// 		return;
// 	current = *garbage_head;
// 	while (current)
// 	{
// 		if(!current->pointer)
// 		{
// 			while(current && !current->pointer)
// 			{
// 				char 
// 				current = current->next;
// 				free(current);
// 			}
// 			if (current)
// 				break;
// 		}
// 		next = current->next;
// 		if (current->pointer)
// 		{
// 			free(current->pointer);
// 			free(current);
// 		}
// 		if (current)
// 			current = next;
// 	}
// 	*garbage_head = NULL;
// }


// char	*gc_realloc(t_all *all, char *old, int big)
// {
// 	int size;
// 	char *new;

// 	if (!old)
// 	{
// 		new = gc_malloc(all, sizeof(char) * (1 + big));
// 		return (new);
// 	}
// 	size = ft_strlen(old);
// 	new = gc_malloc(all, (size + 1 + big));
// 	ft_strlcpy(new, old, size);
// 	return (new);
// }

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
