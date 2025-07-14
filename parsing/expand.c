#include "../mandatory/minishell.h"

void	initialize_data(t_all *all, char *old)
{
	all->data.z = 0;
	all->data.new = NULL;
	all->data.tmp = gc_malloc(all, ft_strlen(old) + 1);
}

void	do_dollar_interrogation(t_all *all)
{
	char	*error_str;

	error_str = gc_itoa(all, all->error_code);
	if (!all->data.new)
		all->data.new = gc_strdup(error_str, all);
	else
	{
		all->data.temp = gc_strjoin(all, all->data.new, error_str);
		all->data.new = all->data.temp;
	}
	all->data.z++;
	return ;
}

void	join_to_new(t_all *all, char *val)
{
	all->data.temp = gc_strjoin(all, all->data.new, val);
	all->data.new = all->data.temp;
}

void	part_one(t_all *all, char *old, char *val)
{
	all->data.z++;
	all->data.t = 0;
	if (old[all->data.z] == '?')
	{
		do_dollar_interrogation(all);
		return ;
	}
	if ((ft_isdigit(old[all->data.z]) || !ft_isalpha(old[all->data.z]))
		&& old[all->data.z] != '_')
	{
		if (old[all->data.z] != 39 && old[all->data.z] != 34)
			all->data.z++;
		return ;
	}
	while (ft_isalnum(old[all->data.z]) == 1 || old[all->data.z] == '_')
		all->data.tmp[all->data.t++] = old[all->data.z++];
	all->data.tmp[all->data.t] = '\0';
	val = find_the_value(all, all->data.tmp);
	if (val && all->data.t > 0)
	{
		if (!all->data.new)
			all->data.new = gc_strdup(val, all);
		else
			join_to_new(all, val);
	}
}

void	part_two(t_all *all, char *old)
{
	char	tmp[2];

	tmp[0] = old[all->data.z];
	tmp[1] = '\0';
	if (!all->data.new)
		all->data.new = gc_strdup(tmp, all);
	else
	{
		all->data.temp = gc_strjoin(all, all->data.new, tmp);
		all->data.new = all->data.temp;
	}
	all->data.z++;
}

void	handle_expand(char *old, t_all *all)
{
	char	*val;

	val = NULL;
	reset_quotes(all);
	while (old && old[all->data.z])
	{
		check_quotes(old[all->data.z], all);
		if (old[all->data.z] == '$' && (old[all->data.z + 1] != ' '
				&& old[all->data.z + 1]) && !all->data.s_quote)
		{
			part_one(all, old, val);
			reset_quotes(all);
		}
		else
			part_two(all, old);
	}
}
