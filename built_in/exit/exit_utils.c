
#include "../mandatory/minishell.h"

int	ft_str_digit(char *str)
{
	int	i;

	if (!str)
		return (-1);
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (str[i] < '0' || str[i] > '9')
		return (-1);
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			i++;
		else
			return (-1);
	}
	return (0);
}

/*******************************************************************************
Only if i'm not a child write exit before exit.
*******************************************************************************/
void	im_a_child(t_all *all)
{
	if (all->pipe.nb_pipe != 0)
		return ;
	ft_putstr_fd("exit\n", 2);
}
