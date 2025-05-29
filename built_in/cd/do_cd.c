
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
void	do_cd_home(t_all *all, char *s)
{
	char no_pwd[4096];
	printf(" JUSTE CD TOUT SEUL ------------\n");
	if (search_env(all, "HOME") == 0)
	{
		s = search_and_return_env(all, "HOME");
		if (search_env(all, "PWD"))
			ft_lstadd_back_env(&all->env, 
			ft_lstnew_env(all, "PWD", gc_strdup_env(find_the_value(all, "HOME")
			, all)));
		else
			replace_env(all, "PWD", gc_strdup_env(find_the_value(all, "HOME"), all));
		if (search_env(all, "OLDPWD"))
			ft_lstadd_back_env(&all->env, 
			ft_lstnew_env(all, "OLDPWD", getcwd(no_pwd, sizeof(no_pwd))));
		else
			replace_env(all, "OLDPWD", getcwd(no_pwd, sizeof(no_pwd)));
	}
	else
	{
		printf("WriteOnMe: cd: HOME not set\n");
		s = NULL;
	}
	if (s)
		if (chdir(s) == -1)
			printf("JE PRINT QUOI COMME ERREUR si chdir echoue??\n");
}

void	do_cd_double_dot(t_all *all)
{
	char *s = NULL;
	char no_pwd[4096];
	char *pwd;
	char *new = NULL;

	printf("je suis la1\n");
	if (!search_env(all, "PWD")) 							//quand pwd existe A MODIFIER PAR IF FIND THE VALUE
	{
		//printf("je suis aussi la2\n");
		pwd = find_the_value(all, "PWD"); //trouve pwd
		//printf("value de PWD=%s\n", pwd);
		new = replace_until_the_last(all, pwd, '/'); //modifie le pwd
		//printf("new value PWD(new) =%s\n", new);
		chdir(new);
		replace_env(all, "PWD", new); //change la value de pwd
		if (search_env(all, "OLDPWD"))					 //quand oldpwd existe
			ft_lstadd_back_env(&all->env, ft_lstnew_env(all, "OLDPWD", s));
		else
			replace_env(all, "OLDPWD", pwd);
	}
	else if (getcwd(no_pwd, sizeof(no_pwd))) //s = "/home/mdsiurds"
	{
		// printf("je suis meme la3\n");
		// printf("new =%s\n", no_pwd);
		new = replace_until_the_last(all, no_pwd, '/'); //new devient /home
		//printf("new =%s\n", new);
		ft_lstadd_back_env(&all->env, ft_lstnew_env(all, "PWD", new));
		if (search_env(all, "OLDPWD"))
			ft_lstadd_back_env(&all->env, ft_lstnew_env(all, "OLDPWD", no_pwd));
		chdir(new);
	}
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
			char no_pwd[4096];
			replace_or_add_env(all, "OLDPWD", getcwd(no_pwd, sizeof(no_pwd)));
		}
		return ;
	}
	else
	{
		char no_pwd[4096];
		old = find_the_value(all, "OLDPWD");
		replace_or_add_env(all, "OLDPWD", getcwd(no_pwd, sizeof(no_pwd)));
		replace_or_add_env(all, "PWD", old);
	}
	if (chdir(old) == -1)
		printf("JE PRINT QUOI COMME ERREUR si chdir echoue??\n");

		//bash: cd: OLDPWD not set
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
	{
		do_cd_home(all, s);
		printf("PWD=%s\nOLDPWD=%s\n", find_the_value(all, "PWD"), find_the_value(all, "OLDPWD"));
		return ;
	}
	else if (ft_strcmp(s, "-") == 0)
	{
		do_cd_minus(all);
		printf("PWD=%s\nOLDPWD=%s\n", find_the_value(all, "PWD"), find_the_value(all, "OLDPWD"));
		return ;
	}
	// if (ft_strcmp(s, ".") == 0)
	// 	do_cd_dot();
	else if (ft_strcmp(s, "..") == 0)
	{
		do_cd_double_dot(all);
		printf("PWD=%s\nOLDPWD=%s\n", find_the_value(all, "PWD"), find_the_value(all, "OLDPWD"));
		return ;
	}
	// if (ft_strcmp(s, "/") == 0)
	// 	do_cd_slash();
	else
		if (chdir(s) == -1)
			perror("WriteOnMe: cd:");
		else
		{
			char no_pwd[4096];
			replace_or_add_env(all, "PWD", getcwd(no_pwd, sizeof(no_pwd)));
		}
		//printf("WriteOnMe: cd: %s No such file or directory\n", s);
	printf("PWD=%s\nOLDPWD=%s\n", find_the_value(all, "PWD"), find_the_value(all, "OLDPWD"));
}
//bash: cd: ..ok: No such file or directory