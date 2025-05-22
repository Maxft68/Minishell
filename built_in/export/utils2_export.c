
#include "minishell.h"

void	copy_list(t_all *all)
{
	t_env		*current;
	t_export	*curr;

	if (!(all)->env)
		return ;
	current = all->env;
	while (current)
	{
		curr = gc_malloc(all, sizeof(t_export));
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
			printf("declare -x ");
			printf("%s=", export->name);
			printf("\"%s\"\n", export->value);
		}
		else
		{
			printf("declare -x ");
			printf("%s\n", export->name);
		}
		export = export->next;
	}
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
		else if (search_env(all, all->data.n) == 1)
			ft_lstadd_back_env(&all->env, ft_lstnew_env(all, all->data.n,
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
