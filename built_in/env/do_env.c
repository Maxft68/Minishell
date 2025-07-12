

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
	char	*path;

	path = "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin";
	all->data.name = gc_malloc_env(all, (all->data.len_name + 1));
	all->data.value = gc_malloc_env(all, (all->data.len_value + 1));
	ft_lstadd_back_env(all, &all->env, ft_lstnew_env(all, "PATH", path));
	all->env_export.nb_line_env = 1;
	ft_lstadd_back_env(all, &all->env, ft_lstnew_env(all, "PWD", ft_pwd(all)));
	all->env_export.nb_line_env = 2;
}

void	normal_env(t_all *all, char **env)
{
	int	j;
	int	i;

	i = 0;
	while (env[i])
	{
		j = 0;
		all->data.len_name = 0;
		all->data.len_value = 0;
		while (env[i][j++] != '=')
			all->data.len_name++;
		all->data.name = gc_malloc_env(all, (all->data.len_name + 1));
		while (env[i][j++])
			all->data.len_value++;
		all->data.value = gc_malloc_env(all, (all->data.len_value + 1));
		split_env(all, env[i]);
		ft_lstadd_back_env(all, &all->env, ft_lstnew_env(all, all->data.name,
				all->data.value));
		i++;
	}
}

void	change_shlvl(t_all *all)
{
	int		old_shlvl;
	char	*new_shlvl;
	char	*shlvl;

	new_shlvl = NULL;
	old_shlvl = 0;
	shlvl = find_the_value(all, "SHLVL");
	if (!shlvl || ft_strlen(shlvl) > 3 || ft_atoi(shlvl) <= 0
		|| ft_atoi(shlvl) >= 999)
		replace_env(all, "SHLVL", "1");
	else
	{
		old_shlvl = ft_atoi(shlvl);
		if (old_shlvl == 999)
			replace_env(all, "SHLVL", "1");
		else
		{
			old_shlvl++;
			new_shlvl = gc_itoa(all, old_shlvl);
			replace_env(all, "SHLVL", new_shlvl);
		}
	}
}

void	do_env(t_all *all, char **env)
{
	int	i;

	i = 0;
	if (!env[i])
		minimal_env(all);
	else
		normal_env(all, env);
	if (search_env(all, "SHLVL"))
	{
		ft_lstadd_back_env(all, &all->env, ft_lstnew_env(all, "SHLVL", "1"));
	}
	else
	{
		change_shlvl(all);
	}
}
