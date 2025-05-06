

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

void	do_env(t_all *all, char **env)
{
	int	i;
	int	j;

	i = 0;
	while (env[i])
	{
		j = 0;
		all->data.len_name = 0;
		all->data.len_value = 0;
		while (env[i][j++] != '=')
			all->data.len_name++;
		all->data.name = malloc(sizeof(char) * (all->data.len_name + 1));
		if (!all->data.name)
			ft_exit("malloc fail", all, 1);
		while (env[i][j++])
			all->data.len_value++;
		all->data.value = malloc(sizeof(char) * (all->data.len_value + 1));
		if (!all->data.value)
			ft_exit("malloc fail", all, 1);
		split_env(all, env[i]);
		ft_lstadd_back_env(&all->env, ft_lstnew_env(all, all->data.name,
				all->data.value));
		i++;
	}
	all->env_export.nb_line_env = i;
}

void	print_node_env(t_env *env)
{
	if (!env)
		return ;
	while (env)
	{
		printf("%s=", env->name);
		printf("%s\n", env->value);
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
		free((*env)->name);
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
		
		//s1s2 = gc_malloc(all, sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
		s1s2 = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
		if (!s1s2)
			ft_exit("Cannot allocate memory", all, 12);
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
	current = all->env;
	if (!all || !all->env)
		ft_exit("pourquoi pas ??", all, 1);
	//env = gc_malloc(all, sizeof(char *) * (all->env_export.nb_line_env + 1));
	env = malloc(sizeof(char *) * (all->env_export.nb_line_env + 1));
	if (!env)
		ft_exit("Cannot allocate memory", all, 12);
	while(current)
	{
		if (!current->name || !current->value)
			ft_exit("Invalid environment variable", all, 1);
		env[j] = strjoin_env(all, current->name, current->value);
		current = current->next;
		j++;
	}
	env[j] = NULL;
	return (env);
}
