
#include "minishell.h"


void	del_export(t_export **export)
{
	t_export	*temp;

	if (!export || !*export)
		return ;
	while (*export)
	{
		temp = (*export)->next;
		if ((*export)->name)
			free((*export)->name);
		if ((*export)->value)
			free((*export)->value);
		free(*export);
		*export = temp;
	}	
}

void	copy_list(t_all *all)
{
	t_env		*current;
	t_export	*curr;

	// del_export(&all->export);
	// all->export = NULL; // test pour ne pas creer des lst export a la pelle
	if (!(all)->env)
		return ;
	current = all->env;
	while (current)
	{
		curr = gc_malloc_env(all, sizeof(t_export));
		curr->value = gc_strdup_env(current->value, all);
		curr->name = gc_strdup_env(current->name, all);
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


/*******************************************************************************
Check if export is: with = / += / without =
*******************************************************************************/

void	export_arg(t_all *all, char *s)
{
	if (ft_strnstr(s, "+=", ft_strlen(s)))
	{
		add_value_env(all, s);
		all->data.add = 1;
	}
	else if (ft_strchr(s, '='))
		do_add_env_next(all, s);
	else
	{
		all->data.n = gc_strdup_env(s, all);
		if (is_alpha_str(all->data.n) == 0) // si le nom nest pas valide
			print_and_null(all, all->data.n);
	}
	if (all->data.n && all->data.add == 0)
	{
		if (all->data.egal == 1 && search_env(all, all->data.n) == 0)
			replace_env(all, all->data.n, all->data.val);
		else if (search_env(all, all->data.n) == 1) //si le node nexiste pas deja
			ft_lstadd_back_env(all, &all->env, ft_lstnew_env(all, all->data.n,
					all->data.val));
	}
}

void	do_add_env(t_all *all)
{
	int		x;
	char	*s;

	x = 0;
	while (all->pipe.cmd_args[all->pipe.nb_pipe][1 + x])
	{
		all->data.val = NULL;
		all->data.n = NULL;
		all->data.egal = 0;
		all->data.add = 0;
		s = gc_strdup_env(all->pipe.cmd_args[all->pipe.nb_pipe][1 + x], all);
		export_arg(all, s);
		x++;
	}
}
































																			//OLDPW






																			//PWD



