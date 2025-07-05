#include "../mandatory/minishell.h"

void	initialize_data(t_all *all, char *old)
{
	all->data.z = 0;
	all->data.j = 0;
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
		return;
	}
	if ((ft_isdigit(old[all->data.z]) || !ft_isalpha(old[all->data.z])) && old[all->data.z] != '_')
		{
			if (old[all->data.z] != 39)
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
		{
			join_to_new(all, val);
			// all->data.temp = gc_strjoin(all, all->data.new, val);// mettre dans un autre fonction
			// all->data.new = all->data.temp;
		}
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
	bool	d_quote;
	bool	s_quote;

	d_quote = false;
	s_quote = false;
	val = NULL;
	while (old && old[all->data.z])
	{
		if (old[all->data.z] == 34 && !d_quote && !s_quote)
			d_quote = true;
		else if (old[all->data.z] == 34 && d_quote && !s_quote)
			d_quote = false;
		else if (old[all->data.z] == 39 && !s_quote && !d_quote)
			s_quote = true;
		else if (old[all->data.z] == 39 && s_quote && !d_quote)
			s_quote = false;
		if (old[all->data.z] == '$' && (old[all->data.z + 1] != ' '
				&& old[all->data.z + 1]) && !s_quote)
		{
			part_one(all, old, val);
			//d_quote = false; // a confirmer
			//s_quote = false; // a confirmer
		}
		else
			part_two(all, old);
	}
}

// void	part_one(t_all *all, char *old, char *val)
// {
// 	all->data.z++;
// 	all->data.t = 0;
// 	while(ft_isalnum(old[all->data.z]) == 1 || old[all->data.z] == '_')
// 		all->data.tmp[all->data.t++] = old[all->data.z++];
// 	all->data.tmp[all->data.t] = '\0';
// 	val = find_the_value(all, all->data.tmp);
// 	if (val && all->data.t > 0)
// 	{
// 		if (!all->data.new)
// 			all->data.new = gc_strdup(val, all);
// 		else
// 		{
// 			all->data.temp = gc_strjoin(all, all->data.new, val);
// 			all->data.new = all->data.temp;
// 		}
// 	}
// }

// void	part_two(t_all *all, char *old)
// {
// 	char tmp[2];
// 	tmp[0] = old[all->data.z];
// 	tmp[1] = '\0';
// 	if (!all->data.new)
// 		all->data.new = gc_strdup(tmp, all);
// 	else
// 	{
// 		all->data.temp = gc_strjoin(all, all->data.new, tmp);
// 		all->data.new = all->data.temp;
// 	}
// 	all->data.z++;
// }

// void	handle_expand(char *old, t_all *all)
// {
// 	char *val;

// 	val = NULL;
// 	while(old && old[all->data.z])
// 	{
// 		if (old[all->data.z] == '$' && old[all->data.z + 1])
// 		{
// 			part_one(all, old, val);
// 		}
// 		else
// 		{
// 			part_two(all, old);
// 		}
// 	}
// }