
#include "minishell.h"

/*******************************************************************************
Check if the node with the same name exist
*******************************************************************************/

int	search_env(t_all *all, char *name)
{
	t_env	*current;

	if (!all->env || !name)
		return (1);
	current = all->env;
	while (current)
	{
		if (ft_strcmp(current->name, name) == 0)
		{
			return(0);
		}
		current = current->next;
	}
	return (1);
}

/*******************************************************************************
If the node with the same name exist, replace the value
*******************************************************************************/
void	replace_env(t_all *all, char *name, char *value)
{
	t_env	*current;
	if (!all->env || !name)
		return ;
	current = all->env;
	while (current)
	{
		if (ft_strcmp(current->name, name) == 0)
		{
			if (value)
				current->value = gc_strdup_env(value, all);
			else
				current->value = gc_strdup_env("", all);
			return;
		}
		current = current->next;
	}
}
/*******************************************************************************
The first carac need to be alpha or '_' the next could be numeric too
*******************************************************************************/

int	is_alpha_str(char *str)
{
	int i;

	if (!str || !str[0])
		return (1); // si chaine vide
	i = 0;
	if (ft_isalpha(str[i]) == 1 || str[i] == '_')
		return (0);
	
	i++;
	while (str[i])
	{
		printf("i = %d\n", i);
		if (ft_isalnum(str[i]) == 0 && str[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

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
			if (current->name && current->next &&
				ft_strcmp(current->name, current->next->name) > 0)
			{
				swap_node(current, current->next);
				swapped = 1;
			}
			current = current->next;
		}
	}
}
