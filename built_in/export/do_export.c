

#include "minishell.h"

int	ft_strcmp(char *s1, char *s2) // a verifier encore pour lol lola lolb 
{
	int i;
	i = 0;
	if (!s1 || !s2)
		return (-1);
	while(s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	do_export(t_all *all)
{
	if((ft_strncmp(all->pipe.cmd_args[all->pipe.nb_pipe][0], "export", 6) == 0
	&& all->pipe.cmd_args[all->pipe.nb_pipe][0][6] == '\0'))
	{
		copy_list(all);
		sort_list(all);
		print_export(all->export);
		all->export = 0;
	}
}

void	swap_node(t_export *a, t_export *b)
{
	char *temp_name;
	char *temp_value;

	temp_name = a->name;
	a->name = b->name;
	b->name = temp_name;

	temp_value = a->value;
	a->value = b->value;
	b->value = temp_value;
}


void	sort_list(t_all *all)
{
	if (!all->export)
		return ;
	int swapped = 1;

	while(swapped == 1)
	{
		swapped = 0;
		t_export *current = all->export;
		while (current && current->next)
		{
			if (current->name && current->next &&
				ft_strcmp(current->name, current->next->name) > 0) // verifier lol lola lolb
			{
				swap_node(current, current->next);
				swapped = 1;
			}
			current = current->next;
		}
	}
}

void	copy_list(t_all *all)
{
	t_env	*current;
	t_export *curr;

	if (!(all)->env)
		return ;

	current = all->env;
	while (current)
	{
		curr = gc_malloc(all, sizeof(t_export));
		if (!curr)
			ft_exit("Cannot allocate memory\n", all, 12);
		curr->value = gc_strdup(current->value, all);
		curr->name = gc_strdup(current->name, all);
		curr->next = NULL;
		ft_lstadd_back_export(&all->export, curr);
		current = current->next;
	}

}

void	ft_lstadd_back_export(t_export **export, t_export *new)
{
	t_export	*current;

	if (!*export)
	{
		*export = new;
		return ;
	}
	current = *export;
	while (current->next)
		current = current->next;
	current->next = new;
	return ;
}

void	print_export(t_export *export)
{
	if (!export)
		return ;
	while (export)
	{
		if (export->value)
		{
			printf ("declare -x ");
			printf ("%s=", export->name);
			printf ("\"%s\"\n", export->value);
		}
		else
		{
			printf ("declare -x ");
			printf ("%s\n", export->name);
		}
		export = export->next;
	}
}


void	*gc_malloc_env(t_all *all, size_t size)
{
	t_garbage_env	*new;
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

void	ft_lstadd_front_gc_env(t_garbage_env **garbage_env, t_garbage_env *new)
{
	t_garbage_env	*second;

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

t_garbage_env	*ft_lstnew(t_all *all, void *alloc)
{
	t_garbage_env	*new;

	new = malloc(sizeof(t_garbage_env));
	if (!new)
		ft_exit("Cannot allocate memory\n", all, 12);
	new->pointer = alloc;
	new->next = NULL;
	return (new);
}

void	free_garbage_env(t_garbage_env **garbage_env_head)
{
	t_garbage_env	*garbage_env;
	t_garbage_env	*temp;

	if (!garbage_env_head || !(*garbage_env_head))
		return ;
	garbage_env = *garbage_env_head;
	while (garbage_env)
	{
		temp = garbage_env->next;
		if (garbage_env->pointer != NULL)
			free(garbage_env->pointer);
		free(garbage_env);
		garbage_env = NULL;
		garbage_env = temp;
	}
	*garbage_env_head = NULL;
}

