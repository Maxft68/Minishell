

#include "minishell.h"

void	do_export(t_all *all)
{
	if((ft_strncmp(all->pipe.cmd_args[all->pipe.nb_pipe][0], "export", 6) == 0
	&& all->pipe.cmd_args[all->pipe.nb_pipe][0][6] == '\0'))
	print_export(all->env);
}

void	print_export(t_env *env)
{
	
	if (!env)
		return ;
	while (env)
	{
		printf ("declare -x ");
		printf ("%s=", env->name);
		printf ("\"%s\"\n", env->value);
		env = env->next;
	}
}

// void	sort_list(t_all *all)
// {
// ajouter un variable dans l'env
	//comparer name
	// verifier si la variable existe
	//copie de list list export
// }

void	*gc_malloc_env(t_all *all, size_t size)
{
	t_garbage_env	*new;
	void		*alloc;

	alloc = malloc(size);
	if (!alloc)
		ft_exit("Cannot allocate memory", all, 12);
	new = ft_lstnew(all, alloc);
	if (!new)
	{
		free(alloc);
		ft_exit("Cannot allocate memory", all, 12);
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
		ft_exit("Cannot allocate memory", all, 12);
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


