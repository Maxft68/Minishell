
#include "minishell.h"

void	print_and_null(t_all *all, char *s)
{
	printf("WriteOnMe: export: `%s': not a valid identifier\n", s);
	all->data.n = NULL;
}
