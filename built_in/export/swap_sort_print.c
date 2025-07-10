
#include "minishell.h"

static	void	swap_node(t_export *a, t_export *b)
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
			if ((!current->name && current->next->name) || 
			(current->name && current->next->name &&
				ft_strcmp(current->name, current->next->name) > 0))
			{
				swap_node(current, current->next);
				swapped = 1;
			}
			current = current->next;
		}
	}
}

void	print_export(t_export *export)
{
	if (!export)
		return ;
	while (export)
	{
		//ft_putstr_fd("JE SUIS BIEN DANS LA BOUCLE PRINT EXPORT\n", 2);
		if (!export->name)
			export = export->next;
		else
		{
			if (export->value)
			{
				// ft_putstr_fd("declare -x ", 2);
				// ft_putstr_fd(export->name, 2);
				// ft_putstr_fd("=\"", 2);
				// ft_putstr_fd(export->value, 2);
				// ft_putstr_fd("\"\n", 2);
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
}
