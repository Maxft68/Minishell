
#include "minishell.h"

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
