
#include "../mandatory/minishell.h"

char	*gc_strdup_env(char *s, t_all *all)
{
	char	*alloc;
	size_t	l;
	if (!s)
		return (NULL);
	l = ft_strlen(s);
	alloc = gc_malloc_env(all, (l + 1) * sizeof(char));
	ft_strlcpy(alloc, s, l + 1);
	return (alloc);
}

char	*gc_substr_env(char *s, unsigned int start, size_t len, t_all *all)
{
	char	*alloc;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (gc_strdup_env("", all));
	if (len > (ft_strlen(s) - start))
		len = (ft_strlen(s) - start);
	alloc = gc_malloc_env(all, (len + 1) * sizeof(char));
	ft_strlcpy(alloc, &s[start], len + 1);
	return (alloc);
}

void	*gc_malloc_env(t_all *all, size_t size)
{
	t_garb_env	*new;
	void		*alloc;

	alloc = malloc(size);
	if (!alloc)
		ft_exit("Cannot allocate memory\n", all, 12);
	new = ft_lstnew(all, alloc);
	if (!new)
	{
		free(alloc);
		ft_exit("Cannot allocate memory\n", all, 12);
	}
	ft_lstadd_front_gc_env(&(all->garbage_env), new);
	return (alloc);
}

void	ft_lstadd_front_gc_env(t_garb_env **garbage_env, t_garb_env *new)
{
	t_garb_env	*second;

	if (!(*garbage_env))
	{
		*garbage_env = new;
		return ;
	}
	second = *garbage_env;
	new->next = second;
	*garbage_env = new;
	return ;
}

void	free_garbage_env(t_garb_env **garbage_env_head)
{
	t_garb_env	*garbage_env;
	t_garb_env	*temp;

	if (!garbage_env_head || !(*garbage_env_head))
		return ;
	garbage_env = *garbage_env_head;
	while (garbage_env)
	{
		temp = garbage_env->next;
		if (garbage_env->pointer != NULL)
			free(garbage_env->pointer);
		free(garbage_env);
		garbage_env = temp;
	}
	*garbage_env_head = NULL;
}
