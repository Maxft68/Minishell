
#include "minishell.h"

void	print_node_env(t_all *all, t_env *env)
{
	if (!env)
		return ;
	if (all->pipe.cmd_args[all->pipe.pipe][1])
	{
		ft_putstr_fd("env: ", 2);
		ft_putstr_fd(all->pipe.cmd_args[all->pipe.pipe][1], 2);
		ft_putstr_fd("\n", 2);
		return ;
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
	int		i;
	int		j;
	char	*s1s2;

	{
		s1s2 = gc_malloc_env(all, (ft_strlen(s1) + ft_strlen(s2) + 2)
				* sizeof(char));
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
			s1s2[i] = s2[j++];
			i++;
		}
		s1s2[i] = '\0';
		return (s1s2);
	}
}

char	**do_char_env(t_all *all)
{
	char	**env;
	t_env	*current;
	int		j;

	j = 0;
	if (!all || !all->env)
		ft_exit("", all, 1);
	current = all->env;
	env = gc_malloc_env(all, sizeof(char *) * (all->env_export.nb_line_env
				+ 2));
	while (current)
	{
		if (!current->name || !current->value)
		{
			while (current && (!current->name || !current->value))
				current = current->next;
			if (!current)
				break ;
		}
		if (current && current->name && current->value)
			env[j++] = strjoin_env(all, current->name, current->value);
		current = current->next;
	}
	return (env[j] = NULL, env);
}
