#include "../mandatory/minishell.h"

void	initialize_data(t_all *all, char *old)
{
	all->data.z = 0;
	all->data.new = NULL;
	all->data.tmp = gc_malloc(all, ft_strlen(old) + 1);
}
void	join_to_new(t_all *all, char *val)
{
	all->data.temp = gc_strjoin(all, all->data.new, val);
	all->data.new = all->data.temp;
}
