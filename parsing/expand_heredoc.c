#include "../mandatory/minishell.h"

void	part_one(t_all *all, char *old, char *val)
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
		all->hd_data.tmp[all->hd_data.j++] = old[all->hd_data.i++];
	all->hd_data.tmp[all->hd_data.j] = '\0';
	val = find_the_value(all, all->hd_data.tmp);
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

void	part_two(t_all *all, char *old)
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

void	handle_expand(char *old, t_all *all)
{
	char *val;
	bool d_quote = false;
	bool s_quote = false;
	val = NULL;
	while(old[all->hd_data.i])
	{
        if (old[all->hd_data.i] == 34 && !d_quote && !s_quote)
            d_quote = true;
        else if (old[all->hd_data.i] == 34 && d_quote && !s_quote)
            d_quote = false;
        else if (old[all->hd_data.i] == 39 && !s_quote && !d_quote)
            s_quote = true;
        else if (old[all->hd_data.i] == 39 && s_quote && !d_quote)
			s_quote = false;
		if (old[all->hd_data.i] == '$' && 
			(old[all->hd_data.i + 1] != ' ' && old[all->hd_data.i + 1]) && !s_quote)
		{
			part_one(all, old, val);
			d_quote = false;
			s_quote = false;
		}
		else
			part_two(all, old);
	}
}
