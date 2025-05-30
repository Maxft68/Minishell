
#include "minishell.h"

static	void	suppr_env(t_all *all, char *name)
{
	t_env	*current;

	if (!all->env)
		return ;
	current = all->env;
	while (current)
	{
		if (ft_strcmp(current->name, name) == 0)
		{
			current->name = NULL;
			current->value = NULL;
			return ;
		}
		current = current->next;
	}
}
void	unset_arg(t_all *all, char *s)
{
	if (search_env(all, s) == 0)
		suppr_env(all, s);
}


void	do_unset(t_all *all)
{
	int		x;
	char	*s;

	x = 0;
	while (all->pipe.cmd_args[all->pipe.nb_pipe][1 + x])
	{
		all->data.val = NULL;
		all->data.n = NULL;
		s = gc_strdup_env(all->pipe.cmd_args[all->pipe.nb_pipe][1 + x], all);
		unset_arg(all, s);
		x++;
	}
}
