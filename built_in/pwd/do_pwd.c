
#include "minishell.h"

void	do_pwd(t_all *all)
{
	char s[4096];
	char *f;

	if (getcwd(s,sizeof(s)))
		printf("%s\n", s);
	else if (find_the_value(all, "PWD"))
	{
		f = find_the_value(all, "PWD");
		printf("%s\n", f);
	}
	all->error_code = 0;
}

char	*ft_pwd(t_all *all)
{
	char s[4096];
	char *f;

	if (getcwd(s,sizeof(s)))
	{
		f = gc_strdup_env(s, all);
		all->error_code = 0;
		return(f);
	}
	else if(find_the_value(all, "PWD"))
	{
		f = find_the_value(all, "PWD");
		all->error_code = 0;
		return(f);
	}
	all->error_code = 0;
	return(NULL);
}

