
#include "../mandatory/minishell.h"

void	initialize_hd_data(char *old, t_all *all)
{
	all->hd_data.i = 0;
	all->hd_data.new = NULL;
	all->hd_data.tmp2 = gc_malloc(all, ft_strlen(old) + 1);
	all->hd_data.hd_escape = false;
}

void	expand_hd(t_all *all, char *old, char *val)
{
	all->hd_data.i++;
	all->hd_data.j = 0;
	if ((ft_isdigit(old[all->hd_data.i]) || !ft_isalpha(old[all->hd_data.i]))
		&& old[all->hd_data.i] != '_')
	{
		if (old[all->hd_data.i] != 39)
			all->hd_data.i++;
		return;
	}
	while(ft_isalnum(old[all->hd_data.i]) == 1 || old[all->hd_data.i] == '_')
		all->hd_data.tmp2[all->hd_data.j++] = old[all->hd_data.i++];
	all->hd_data.tmp2[all->hd_data.j] = '\0';
	val = find_the_value(all, all->hd_data.tmp2);
	if (val && all->hd_data.j > 0)
	{
		if (!all->hd_data.new)
			all->hd_data.new = gc_strdup(val, all);
		else
		{
			all->hd_data.tmp = gc_strjoin(all, all->hd_data.new, val);
			all->hd_data.new = all->hd_data.tmp;
		}
	}
}

void	no_hd_expand(t_all *all, char *old)
{
	char tmp[2];

	tmp[0] = old[all->hd_data.i];
	tmp[1] = '\0';
	if (!all->hd_data.new)
		all->hd_data.new = gc_strdup(tmp, all);
	else
	{
		all->hd_data.tmp = gc_strjoin(all, all->hd_data.new, tmp);
		all->hd_data.new = all->hd_data.tmp;
	}
	all->hd_data.i++;
}

void	handle_hd_expand(char *old, t_all *all)
{
	char *val;

	val = NULL;
	reset_quotes(all);
	while(old[all->hd_data.i])
	{
		check_quotes(old[all->hd_data.i], all);
		if (old[all->hd_data.i] == '$' && 
			(old[all->hd_data.i + 1] != ' ' && old[all->hd_data.i + 1]) && !all->data.s_quote)
		{
			expand_hd(all, old, val);
			reset_quotes(all);
		}
		else
			no_hd_expand(all, old);
	}
}
