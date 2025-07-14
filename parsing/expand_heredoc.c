
#include "../mandatory/minishell.h"

void	hd_do_dollar_question(t_all *all)
{
	char	*error_str;

	error_str = gc_itoa(all, all->error_code);
	if (!all->hd_data.new)
		all->hd_data.new = gc_strdup(error_str, all);
	else
	{
		all->hd_data.tmp = gc_strjoin(all, all->hd_data.new, error_str);
		all->hd_data.new = all->hd_data.tmp;
	}
	all->hd_data.i++;
	return ;
}

void	expand_hd(t_all *all, char *old, char *val)
{
	all->hd_data.i++;
	all->hd_data.j = 0;
	if (old[all->hd_data.i] == '?')
	{
		hd_do_dollar_question(all);
		return ;
	}
	if ((ft_isdigit(old[all->hd_data.i]) || !ft_isalpha(old[all->hd_data.i]))
		&& old[all->hd_data.i] != '_')
	{
		if (old[all->hd_data.i] != 39)
			all->hd_data.i++;
		return ;
	}
	while (ft_isalnum(old[all->hd_data.i]) == 1 || old[all->hd_data.i] == '_')
		all->hd_data.tmp2[all->hd_data.j++] = old[all->hd_data.i++];
	all->hd_data.tmp2[all->hd_data.j] = '\0';
	val = find_the_value(all, all->hd_data.tmp2);
	if (val && all->hd_data.j > 0)
	{
		if (!all->hd_data.new)
			all->hd_data.new = gc_strdup(val, all);
		else
			hd_join_to_new(all, val);
	}
}

void	no_hd_expand(t_all *all, char *old)
{
	char	tmp[2];

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
	char	*val;

	val = NULL;
	reset_quotes(all);
	while (old[all->hd_data.i])
	{
		check_quotes(old[all->hd_data.i], all);
		if (old[all->hd_data.i] == '$' && (old[all->hd_data.i + 1] != ' '
				&& old[all->hd_data.i + 1]) && !all->data.s_quote
			&& !as_quotes(old))
		{
			expand_hd(all, old, val);
			reset_quotes(all);
		}
		else
			no_hd_expand(all, old);
	}
}
