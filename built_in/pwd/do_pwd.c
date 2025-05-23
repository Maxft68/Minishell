
#include "minishell.h"

void	do_pwd(t_all *all)
{
	char s[4096];

	if (getcwd(s,sizeof(s)))
		printf("%s\n", s);
	// code erreur TOUJOURS A 0
	(void) all;
}
