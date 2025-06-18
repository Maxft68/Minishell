
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
int	replace_env(t_all *all, char *name, char *value)
{
	t_env	*current;
	if (!all->env || !name)
		return (0);
	current = all->env;
	while (current)
	{
		if (!current->name || !current->value)
		{
			while(current && (!current->name || !current->value))
				current = current->next;
			if (!current)
				break;
		}
		if (ft_strcmp(current->name, name) == 0)
		{
			if(value)
			{
				if (ft_strlen(value) < ft_strlen(current->value))
					ft_strlcpy(current->value, value, ft_strlen(value) + 1);
				else
				{
					free(current->value);
					current->value = gc_strdup_env(value, all);
				}
			}
			else
			{
				free(current->value);
				current->value = gc_strdup_env("", all);
			}
			return (1);
			// if (value)
			// 	current->value = gc_strdup_env(value, all);
			// else
			// 	current->value = gc_strdup_env("", all);
			// return (1);
		}
		if (current)
			current = current->next;
	}
	return(0);
}
/*******************************************************************************
If the node exist replace the value, if not, create the node
*******************************************************************************/
void	replace_or_add_env(t_all *all, char *name, char *value)
{
	if (replace_env(all, name, value) == 0)
		ft_lstadd_back_env(all, &all->env, ft_lstnew_env(all, name, value));
}

/*******************************************************************************
The first carac need to be alpha or '_' the next could be numeric too
*******************************************************************************/

int	is_alpha_str(char *str)
{
	int i;
	i = 0;
	
	if (!str || !str[0])
		return (0); // si chaine vide
	if (str[i] == '_')
		i++;
	else if (ft_isalpha(str[i]) == 1)
		i++;
	else if (ft_isalpha(str[i]) != 1)
		return (0);
	while (str[i])
	{
		if (ft_isalnum(str[i]) == 0 && str[i] != '_')
			return (1);
		i++;
	}
	return (1);
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
