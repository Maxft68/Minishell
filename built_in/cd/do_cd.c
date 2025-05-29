
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

void	do_cd_double_dot(t_all *all)
{
	char *s = NULL;
	char no_pwd[4096];
	char *pwd;
	char *new;
	char *cd;

	cd = ft_strdup("..");
	printf("je suis la1\n");
	if (!search_env(all, "PWD")) 							//quand pwd existe
	{
		printf("je suis aussi la2\n");
		pwd = find_the_value(all, "PWD"); //trouve pwd
		printf("value de PWD=%s\n", pwd);
		new = replace_until_the_last(all, pwd, '/'); //modifie le pwd
		printf("new value =%s\n", new);
		chdir(cd);
		replace_env(all, "PWD", new); //change la value de pwd
		printf("new value 2e fois =%s\n", new);
		if (search_env(all, "OLDPWD"))					 //quand oldpwd existe
		{
			printf("ici ???\n");
			ft_lstadd_back_env(&all->env, ft_lstnew_env(all, "OLDPWD", s));
		}
		else
		{
			printf(" ou la ???\n");
			replace_env(all, "OLDPWD", pwd);
		}
		copy_list(all);
		sort_list(all);
	}
	else if (getcwd(s,sizeof(no_pwd))) //s = "/home/mdsiurds"
	{
		printf("je suis meme la3\n");
		new = replace_until_the_last(all, no_pwd, '/'); //new devient /home

		ft_lstadd_back_env(&all->env, ft_lstnew_env(all, "PWD", new));
		if (search_env(all, "OLDPWD"))
			ft_lstadd_back_env(&all->env, ft_lstnew_env(all, "OLDPWD", no_pwd));
		copy_list(all);
		sort_list(all);
		chdir(new);
	}
}


void	do_cd(t_all *all)
{
	char *s;

	s = NULL;
	if (!all->pipe.cmd_args[all->pipe.nb_pipe]) //JUSTE UN TEST 
	{
		printf("JE DEVRAIS PAS ETRE LA ?????????");
		return ;
	}
	if (all->pipe.cmd_args[all->pipe.nb_pipe][2])
		printf("WriteOnMe: cd: too many arguments");
	if (all->pipe.cmd_args[all->pipe.nb_pipe][1])
		s = all->pipe.cmd_args[all->pipe.nb_pipe][1];
	if (!s || ft_strcmp(s, "~") == 0)// retourne a HOME
		do_cd_home(all, s);
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
//coucou