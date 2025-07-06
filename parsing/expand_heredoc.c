#include "../mandatory/minishell.h"

//initialiser hd_data!!!!!!

void	initialize_hd_data(char *old, t_all *all)
{
	all->hd_data.i = 0;
	// all->hd_data.j = 0;
	all->hd_data.new = NULL;
	all->hd_data.tmp = gc_malloc(all, ft_strlen(old) + 1);
}

void	expand_hd(t_all *all, char *old, char *val)
{
	int b = 0;

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
		printf("%d--->", b);
		printf("%s\n", all->hd_data.new);
		b++;
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
	// bool d_quote = false;
	// bool s_quote = false;
	val = NULL;
	reset_quotes(all);
	while(old[all->hd_data.i])
	{
        // if (old[all->hd_data.i] == 34 && !d_quote && !s_quote)
        //     d_quote = true;
        // else if (old[all->hd_data.i] == 34 && d_quote && !s_quote)
        //     d_quote = false;
        // else if (old[all->hd_data.i] == 39 && !s_quote && !d_quote)
        //     s_quote = true;
        // else if (old[all->hd_data.i] == 39 && s_quote && !d_quote)
		// 	s_quote = false;
		check_quotes(old[all->hd_data.i], all);
		if (old[all->hd_data.i] == '$' && 
			(old[all->hd_data.i + 1] != ' ' && old[all->hd_data.i + 1]) && !all->data.s_quote)
		{
			expand_hd(all, old, val);
			reset_quotes(all);
			// d_quote = false;
			// s_quote = false;
		}
		else
			no_hd_expand(all, old);
	}
}
