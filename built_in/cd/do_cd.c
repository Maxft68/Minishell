
#include "minishell.h"

void	test_the_path(t_all *all, char *s)
{
	if (s)
	{
		char *str = gc_strjoin(all, "WriteOnMe: cd ", s);
		if (chdir(s) == -1)
			perror(str);
	}
	// set PWD ET OLDPWD ICI ??	
}

// char	*search_and_return_env(t_all *all, char *name)
// {
// 	t_env	*current;

// 	if (!all->env || !name)
// 		return (NULL);
// 	current = all->env;
// 	while (current)
// 	{
// 		if (ft_strcmp(current->name, name) == 0 && current->value)
// 		{
// 			return(current->value);
// 		}
// 		current = current->next;
// 	}
// 	return (NULL);
// }


char	*replace_until_the_last(t_all *all, char *s, int c)
{
	size_t	i;
	int		j;
	char *new;
	
	i = ft_strlen(s);
	j = i;
	while (i > 0)
	{
		if (s[i] != (char)c)
			i--;
		else
		{
			new = gc_substr_env(s, 0, j - (j - i), all);
			return (new);
		}
	}
	if (s[i] == (char)c)
		return (new = gc_substr_env(s, 0, 1, all));
	return (NULL);
}

char	*find_the_value(t_all *all, char *name)
{
	t_env	*current;
	if (!all->env || !name)
		return (NULL);
	current = all->env;
	while (current)
	{
		if (ft_strcmp(current->name, name) == 0)
		{
			if (current->value)
			return(gc_strdup_env(current->value, all));
		}
		current = current->next;
	}
	return (NULL);
}
void	do_cd_home(t_all *all, char *s)
{
	if (find_the_value(all, "HOME"))
	{
		s = find_the_value(all, "HOME");
		replace_or_add_env(all, "OLDPWD", ft_pwd(all));
		replace_or_add_env(all, "PWD", s);
	}
	else
	{
		printf("WriteOnMe: cd: HOME not set\n");
		s = NULL;
	}
	if (s)
		test_the_path(all, s);
	copy_list(all);
	sort_list(all);
}

void	do_cd_double_dot(t_all *all)
{
	char *new = NULL;

	if (ft_pwd(all))
	{
		new = replace_until_the_last(all, ft_pwd(all), '/');
		replace_or_add_env(all, "OLDPWD", ft_pwd(all));
		replace_or_add_env(all, "PWD", new);
	}
	if (new)
		test_the_path(all, new);
	copy_list(all);
	sort_list(all);
}

void	do_cd_minus(t_all *all)
{
	char *old;

	if (!find_the_value(all, "OLDPWD"))
	{
		printf("WriteOnMe: cd: OLDPWD not set\n");
		if (search_env(all, "OLDPWD"))
		{
			replace_or_add_env(all, "OLDPWD", ft_pwd(all));
			replace_or_add_env(all, "PWD", ft_pwd(all));
		}
		return ;
	}
	else
	{
		old = find_the_value(all, "OLDPWD");
		replace_or_add_env(all, "OLDPWD", ft_pwd(all));
		replace_or_add_env(all, "PWD", old);
	}
	if (old)
		test_the_path(all, old);
	copy_list(all);
	sort_list(all);
}

void	do_cd(t_all *all)
{
	char *s;

	s = NULL;
	if (all->pipe.cmd_args[all->pipe.nb_pipe][1] &&
		all->pipe.cmd_args[all->pipe.nb_pipe][2])
	{
		printf("WriteOnMe: cd: too many arguments\n");
		return;
	}
	if (all->pipe.cmd_args[all->pipe.nb_pipe][1])
		s = all->pipe.cmd_args[all->pipe.nb_pipe][1];
	if (!s || ft_strcmp(s, "~") == 0)
		do_cd_home(all, s);
	else if (ft_strcmp(s, "-") == 0)
		do_cd_minus(all);
	else if (ft_strcmp(s, "..") == 0)
		do_cd_double_dot(all);
	else
	{
		test_the_path(all, s);
		// 	replace_or_add_env(all, "PWD", ft_pwd(all)); set OLDPWD ET PWD ensuite !!
	}
	printf("PWD=%s\nOLDPWD=%s\n", find_the_value(all, "PWD"), find_the_value(all, "OLDPWD"));
}
