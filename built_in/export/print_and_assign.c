
#include "../../mandatory/minishell.h"

void	print_and_null(t_all *all, char *s)
{
	ft_putstr_fd("WriteOnMe: export: `", 2);
	if (s)
		ft_putstr_fd(s, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	all->data.n = NULL;
	all->error_code = 1;
	all->data.val = NULL;
}
