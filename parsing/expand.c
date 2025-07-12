#include "../mandatory/minishell.h"

void	initialize_data(t_all *all, char *old)
{
	all->data.z = 0;
	all->data.new = NULL;
	all->data.tmp = gc_malloc(all, ft_strlen(old) + 1);
}

void	do_dollar_interrogation(t_all *all)//, char *str, char *tmp, int index)
{
	char	*error_str;

	error_str = gc_itoa(all, all->error_code);
	if (!all->data.new)
		all->data.new = gc_strdup(error_str, all);
	// if (!str)
	// 	str = gc_strdup(error_str, all);
	else
	{
		all->data.temp = gc_strjoin(all, all->data.new, error_str);
		all->data.new = all->data.temp;
		// tmp = gc_strjoin(all, str, error_str);
		// str = tmp;
	}
	all->data.z++;
	// index++;
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
		do_dollar_interrogation(all);//, all->data.new, all->data.temp, all->data.z);
		return;
	}
	if (old[all->data.z] == '"')
	{
		all->data.d_quote = true;
		all->data.z++;
		return ;
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
	char *val;
	// bool d_quote = false;
	// bool s_quote = false;
	val = NULL;
	reset_quotes(all);
	while(old && old[all->data.z])
	{
		check_quotes(old[all->data.z], all);
		if (old[all->data.z] == '$' && (old[all->data.z + 1] != ' ' && 
			old[all->data.z + 1] != 34 && old[all->data.z + 1] != 39 &&
		old[all->data.z + 1]) && !all->data.s_quote)
		{
			//printf("part_one et data.z = %c\n",old[all->data.z]);
			part_one(all, old, val);
			reset_quotes(all);
		}
		else
		{
			//printf("part_two et data.z = %c\n",old[all->data.z]);
			part_two(all, old);
		}
	}
}

// if (old[all->data.z] == '$' && (old[all->data.z + 1] != ' ' && 
//             old[all->data.z + 1] != 34 && old[all->data.z + 1] != 39 &&
//         old[all->data.z + 1]) && !all->data.s_quote)// && !all->data.d_quote)
//         {
//             part_one(all, old, val);
//             reset_quotes(all);
//         }

// if (old[all->data.z] == '$' && 
//             (old[all->data.z + 1] != ' ' && old[all->data.z + 1]) && 
//             !all->data.s_quote && !all->data.d_quote)
//         {
//             part_one(all, old, val);
//             reset_quotes(all);
//             // d_quote = false;
//             // s_quote = false;
//         }