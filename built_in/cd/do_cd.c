
#include "minishell.h"


char	*search_and_return_env(t_all *all, char *name)
{
	t_env	*current;

	if (!all->env || !name)
		return (NULL);
	current = all->env;
	while (current)
	{
		if (ft_strcmp(current->name, name) == 0 && current->value)
		{
			return(current->value);
		}
		current = current->next;
	}
	return (NULL);
}
void	do_cd_home(t_all *all, char *s)
{
	if (search_env(all, "HOME") == 0)
		s = search_and_return_env(all, "HOME");
	else
		printf("WriteOnMe: cd: HOME not set\n");
	if (s)
		chdir(s);
		//modifier PWD ?
}

// void	do_cd_minus(t_all *all)
// {
// // 	mdsiurds@k1r4p4:/$ unset OLDPWD
// // mdsiurds@k1r4p4:/$ cd -
// // bash: cd: OLDPWD not set

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
			new = gc_substr_env(s, 0, j - i, all);
			return (new);
		}
	}
	if (s[i] == (char)c)
		return (new = gc_substr_env(s, 0, 1, all));
	return (NULL);
}

void	do_cd_double_dot(t_all *all)
{
	char s[4096];
	char *new;

	if (getcwd(s,sizeof(s))) //s = "/home/mdsiurds"
	{
		new = replace_until_the_last(all, s, '/'); //new devient /home
		if (!new)
		{
			chdir(new);
			replace_env(all, "OLDPWD", s);
		}
	}
}


void	do_cd(t_all *all)
{
	char *s;

	s = NULL;
	if (all->pipe.cmd_args[all->pipe.nb_pipe][2])
		printf("WriteOnMe: cd: too many arguments");
	if (all->pipe.cmd_args[all->pipe.nb_pipe][1])
		s = all->pipe.cmd_args[all->pipe.nb_pipe][1];
	// if (!s || ft_strcmp(s, "~") == 0)// retourne a HOME
	// 	do_cd_home(all, s);
	// if (ft_strcmp(s, "-") == 0)
	// 	do_cd_minus();
	// if (ft_strcmp(s, ".") == 0)
	// 	do_cd_dot();
	if (ft_strcmp(s, "..") == 0)
		do_cd_double_dot(all);
	// if (ft_strcmp(s, "/") == 0)
	// 	do_cd_slash();
	else
		printf("WriteOnMe: cd: %s No such file or directory\n", s);

}
//bash: cd: ..ok: No such file or directory