
#include "../mandatory/minishell.h"

void    reset_quotes(t_all *all)
{
    all->data.s_quote = false;
    all->data.d_quote = false;
}

void	check_quotes(char c, t_all *all)
{
	if (c == 34 && !all->data.d_quote && !all->data.s_quote)
        all->data.d_quote = true;
    else if (c == 34 && all->data.d_quote && !all->data.s_quote)
        all->data.d_quote = false;
    else if (c == 39 && !all->data.s_quote && !all->data.d_quote)
        all->data.s_quote = true;
    else if (c == 39 && all->data.s_quote && !all->data.d_quote)
		all->data.s_quote = false;
}

int	verif_quoted(char *input, t_all *all)
{

	int i;
	int c;
	// bool d_quote = false;
	// bool s_quote = false;
	i = 0;
    reset_quotes(all);
	while(input[i])
	{
		c = input[i];
        // if (c == 34 && !d_quote && !s_quote)
        //     d_quote = true;
        // else if (c == 34 && d_quote && !s_quote)
        //     d_quote = false;
        // else if (c == 39 && !s_quote && !d_quote)
        //     s_quote = true;
        // else if (c == 39 && s_quote && !d_quote)
		// 	s_quote = false;
        check_quotes(c, all);
		i++;
	}
	if (all->data.s_quote || all->data.d_quote)
	{
		ft_putstr_fd("Quotes Syntax error\n", 2);
		return(-1);
	}
	return (0);
}