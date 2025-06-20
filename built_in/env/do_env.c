

#include "minishell.h"

void	split_env(t_all *all, char *env)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (env[i] != '=')
	{
		all->data.name[i] = env[i];
		i++;
	}
	all->data.name[i] = '\0';
	i++;
	while (env[i])
	{
		all->data.value[j] = env[i];
		j++;
		i++;
	}
	all->data.value[j] = '\0';
}

void	minimal_env(t_all *all)
{
	char *path;

	path = "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin";
	all->data.name = gc_malloc_env(all, (all->data.len_name + 1));
	if (!all->data.name)
		ft_exit("Cannot allocate memory1\n", all, 12);
	all->data.value = gc_malloc_env(all, (all->data.len_value + 1));
	if (!all->data.value)
		ft_exit("Cannot allocate memory2\n", all, 12);
	ft_lstadd_back_env(all, &all->env, ft_lstnew_env(all, "PATH", path));
	all->env_export.nb_line_env = 1;
	//printf("jai %d variables dans env(minimal env)\n", all->env_export.nb_line_env);
}

void	normal_env(t_all *all, char **env)
{
	int j;
	int i;

	i = 0;
	while (env[i])
	{
		j = 0;
		all->data.len_name = 0;
		all->data.len_value = 0;
		while (env[i][j++] != '=')
			all->data.len_name++;
		all->data.name = gc_malloc_env(all, (all->data.len_name + 1));
		if (!all->data.name)
			ft_exit("Cannot allocate memory1.1\n", all, 12);
		while (env[i][j++])
			all->data.len_value++;
		all->data.value = gc_malloc_env(all, (all->data.len_value + 1));
		if (!all->data.value)
			ft_exit("Cannot allocate memory2.1\n", all, 12);
		split_env(all, env[i]);
		ft_lstadd_back_env(all, &all->env, ft_lstnew_env(all, all->data.name,
				all->data.value));
		//printf("jai %d variables dans env(normal env)\n", all->env_export.nb_line_env);
		i++; // test foireux
	}
	//all->env_export.nb_line_env = i;
}

void	change_shlvl(t_all *all)
{
	int	old_shlvl;
	char *new_shlvl;
	char *shlvl;

	new_shlvl = NULL;
	old_shlvl = 0;
	shlvl = find_the_value(all, "SHLVL");
	printf("shvalue= %s\n", shlvl);
	printf("len = %zu\n", ft_strlen(find_the_value(all, "SHLVL")));
	printf("atoi = %d\n",ft_atoi(find_the_value(all, "SHLVL")));
	if(!shlvl  || ft_strlen(shlvl) > 3 || ft_atoi(shlvl) <= 0 || ft_atoi(shlvl) >= 999)
		replace_env(all, "SHLVL", "1");
	else
	{
		old_shlvl = ft_atoi(shlvl);
		if (old_shlvl == 999)
			replace_env(all, "SHLVL", "1");
		else
		{
			old_shlvl ++;
			new_shlvl = gc_itoa(all, old_shlvl);
			replace_env(all, "SHLVL", new_shlvl);
		}
	}
}

void	do_env(t_all *all, char **env)
{
	int i;

	i = 0;
	if (!env[i])
		minimal_env(all);
	else
		normal_env(all, env);
	if (search_env(all, "SHLVL")) //si il existe pas
	{
		ft_lstadd_back_env(all, &all->env, ft_lstnew_env(all, "SHLVL", "1"));
	}
	else
	{
		change_shlvl(all);
	}
}

void	print_node_env(t_all *all, t_env *env)
{
	if (!env)
		return ;
	if (all->pipe.cmd_args[all->pipe.pipe][1])
	{
		ft_putstr_fd("env: ", 2);
		ft_putstr_fd(all->pipe.cmd_args[all->pipe.pipe][1], 2);
		ft_putstr_fd("\n", 2);
		return;
	}
	while (env)
	{
		if (env->value)
		{
			printf("%s=", env->name);
			printf("%s\n", env->value);
		}
		env = env->next;
	}
}

void	free_env(t_env **env)
{
	t_env	*temp;

	if (!env || !*env)
		return ;
	while (*env)
	{
		temp = (*env)->next;
		if ((*env)->name)
			free((*env)->name);
		if ((*env)->value)
			free((*env)->value);
		free(*env);
		*env = temp;
	}
}

char	*strjoin_env(t_all *all, char *s1, char *s2)
{
	{
		int		i;
		int		j;
		char	*s1s2;

		s1s2 = gc_malloc_env(all, (ft_strlen(s1) + ft_strlen(s2) + 2) * sizeof(char));
		if (!s1s2)
			ft_exit("Cannot allocate memory3\n", all, 12);
		i = 0;
		j = 0;
		while (s1 && s1[i])
		{
			s1s2[i] = s1[i];
			i++;
		}
		s1s2[i] = '=';
		i++;
		while (s2 && s2[j])
		{
			s1s2[i] = s2[j];
			i++;
			j++;
		}
		s1s2[i] = '\0';
		return (s1s2);
	}
}

char	**do_char_env(t_all *all)
{
	char **env;
	t_env	*current;
	int j;
	j = 0;
	if (!all || !all->env)
		ft_exit("pourquoi pas ??", all, 1);
	current = all->env;
	env = gc_malloc_env(all, sizeof(char *) * (all->env_export.nb_line_env + 1));
	if (!env)
		ft_exit("Cannot allocate memory4\n", all, 12);
	while(current)
	{
		if (!current->name || !current->value)
		{
			while(current && (!current->name || !current->value))
				current = current->next;
			if (!current)
				break;
		}
		if (current && current->name && current->value)
		{
			env[j] = strjoin_env(all, current->name, current->value);
			j++;
		}
		if (current)
			current = current->next;
	}
	env[j] = NULL;
	return (env);
}

