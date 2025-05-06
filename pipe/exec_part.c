#include "minishell.h"

void	exec_part(t_all *all)
{
	if (!is_built_in(all))
			exec_cmd(all); 
}