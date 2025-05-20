

#include "minishell.h"

void	add_env(t_all *all, char *name, char *value)
{
	t_env	*current;
	//printf("ca rentre la ?\n");
	if (!all->env || !name)
	return ;
	current = all->env;
	while (current)
	{
		if (ft_strcmp(current->name, name) == 0) // si le nom correspond
		{
			//printf("ca rentre pas la ?\n");
			if (value)
				current->value = gc_strjoin_env(all, current->value, value); //creer strjoin_env
			else
				current->value = gc_strdup_env("", all); // si pas de valeur, mettre une chaine vide
			return;
		}
		current = current->next;
	}
}

void	add_value_env(t_all *all, char *s) //  +=
{
	int i;

	i = 0;
	char *value;
	char *name;
	int egal = 0;

	value = NULL;
	name = NULL;
	while(s[i] && s[i] != '=')
		i++;
	if (s[i] == '=' && i > 0 && s[i - 1] == '+') // si = nest pas le premier caractere
	{
		egal = 1;
		name = gc_strdup_env(gc_substr_env(s, 0, i - 1, all), all);
		//printf("name = << %s >>\n", name);
		if (is_alpha_str(name)) // si le nom nest pas valide
		{
			printf("minishell: export: << %s >>: not a valid identifier\n", s);
			name = NULL;
		}
		if (s[i + 1] && name)
			value = gc_strdup_env(gc_substr_env(s, i + 1, ft_strlen(s) - i - 1, all), all);
		else
			value = gc_strdup_env("", all); // si pas de valeur apres le =de
	}
	if(name) // et value ?
	{
		if (egal == 1 && search_env(all, name) == 0)
			add_env(all, name, value);//je remplace quqnd je trouve la valeur
		else if (search_env(all, name) == 1) // sinon jajoute
			ft_lstadd_back_env(&all->env, ft_lstnew_env(all, name, value));
	}
	return ;
}

void	do_add_env(t_all *all)
{
	int i;
	i = 0;
	char *s;
	char *value;
	char *name;
	static int x = 0;
	int egal = 0;
	int add = 0;

	value = NULL;
	name = NULL;
	if (all->pipe.cmd_args[all->pipe.nb_pipe][1 + x])
		s = gc_strdup_env(all->pipe.cmd_args[all->pipe.nb_pipe][1 + x], all);
	else // si plus dargs
	{
		x = 0;
		return ; // si plus dargs
	}
	if (ft_strnstr(s, "+=", ft_strlen(s)))
	{
		add_value_env(all, s);
		add = 1;
	}
	else if (ft_strchr(s, '=')) // si il y a un =
	{
		while(s[i] && s[i] != '=')
			i++;
	
		if (s[i] == '=' && i > 0 && s[i - 1] && s[i - 1] != ' ') // si = nest pas le premier caractere
		{
			egal = 1;
			name = gc_strdup_env(gc_substr_env(s, 0, i, all), all);
			if (is_alpha_str(name)) // si le nom nest pas valide
			{
				printf("minishell: export: << %s >>: not a valid identifier\n", name);
				name = NULL;
			}
			if (s[i + 1] && name)
				value = gc_strdup_env(gc_substr_env(s, i + 1, ft_strlen(s) - i - 1, all), all);
			else
				value = gc_strdup_env("", all); // si pas de valeur apres le =de
		}
	}
	else //si pas de =
	{
		name = gc_strdup_env(s, all);
		if (is_alpha_str(name)) // si le nom nest pas valide
			{
				printf("minishell: export: << %s >>: not a valid identifier\n", name);
				name = NULL;
			}
		value = NULL;
	}
	if(name && add == 0) // et value ?
	{
		if (egal == 1 && search_env(all, name) == 0)
			replace_env(all, name, value);//je remplace quqnd je trouve la valeur
		else if (search_env(all, name) == 1) // sinon jajoute
			ft_lstadd_back_env(&all->env, ft_lstnew_env(all, name, value));
	}
	x++;
	do_add_env(all);
	return ;
}

void	do_export(t_all *all)
{
	if (ft_strncmp(all->pipe.cmd_args[all->pipe.nb_pipe][0], "export", 6) == 0
	&& all->pipe.cmd_args[all->pipe.nb_pipe][0][6] == '\0' &&
	!all->pipe.cmd_args[all->pipe.nb_pipe][1])
	{
		all->export = NULL;  // Réinitialiser la liste export avant de la remplir
		copy_list(all);
		sort_list(all);
		print_export(all->export);
	}
	else if (ft_strncmp(all->pipe.cmd_args[all->pipe.nb_pipe][0], "export", 6) == 0
	&& all->pipe.cmd_args[all->pipe.nb_pipe][0][6] == '\0' &&
	all->pipe.cmd_args[all->pipe.nb_pipe][1])
		do_add_env(all);
}

t_garb_env	*ft_lstnew(t_all *all, void *alloc)
{
	t_garb_env	*new;

	new = malloc(sizeof(t_garb_env));
	if (!new)
		ft_exit("Cannot allocate memory\n", all, 12);
	new->pointer = alloc;
	new->next = NULL;
	return (new);
}


