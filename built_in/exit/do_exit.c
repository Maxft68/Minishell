

#include "../../mandatory/minishell.h"

static int	part_two_long(t_all *all, char *str)
{
	all->exit.end = all->exit.i;
	while (str[all->exit.i] == ' ' || (str[all->exit.i] >= 9
			&& str[all->exit.i] <= 13))
		all->exit.i++;
	if (all->exit.start != all->exit.end)
	{
		ft_memmove(str, str + (all->exit.start - all->exit.negative),
			all->exit.end - (all->exit.start - all->exit.negative));
		str[all->exit.end - (all->exit.start - all->exit.negative)] = '\0';
		if (all->exit.negative == 1)
			str[0] = '-';
	}
	if ((all->exit.end - all->exit.start) > 19)
		return (1);
	if ((all->exit.end - all->exit.start) < 19)
		return (0);
	if (ft_strcmp(str, "9223372036854775808") >= 0 && all->exit.negative == 0)
		return (1);
	if (ft_strcmp(str, "9223372036854775809") >= 0 && all->exit.negative == 1)
		return (1);
	else
		return (0);
}

static int	is_long_long(t_all *all, char *str)
{
	all->exit.i = 0;
	all->exit.negative = 0;
	while (str[all->exit.i] == ' ' || (str[all->exit.i] >= 9
			&& str[all->exit.i] <= 13))
		all->exit.i++;
	if (str[all->exit.i] == '-' || str[all->exit.i] == '+')
	{
		all->exit.sign = 1;
		if (str[all->exit.i] == '-')
			all->exit.negative = 1;
		all->exit.i++;
		if (str[all->exit.i] == '-' || str[all->exit.i] == '+')
		{
			ft_putstr_fd("WriteOnMe: exit: ", 2);
			ft_putstr_fd(all->pipe.cmd_args[all->pipe.pipe][1], 2);
			ft_exit(": numeric argument required\n", all, 2);
		}
	}
	while (str[all->exit.i] == '0')
		all->exit.i++;
	all->exit.start = all->exit.i;
	while (str[all->exit.i] >= '0' && str[all->exit.i] <= '9')
		all->exit.i++;
	return (part_two_long(all, str));
}

/*******************************************************************************
If more then 1 arg, check if the first is a digit, and if it is a long long.
*******************************************************************************/
static void	exit_args(t_all *all)
{
	if (!ft_str_digit(all->pipe.cmd_args[all->pipe.pipe][1]))
	{
		if (is_long_long(all, all->pipe.cmd_args[all->pipe.pipe][1]))
		{
			im_a_child(all);
			ft_putstr_fd("WriteOnMe: exit: ", 2);
			ft_putstr_fd(all->pipe.cmd_args[all->pipe.pipe][1], 2);
			ft_exit(": numeric argument required\n", all, 2);
		}
		else
		{
			im_a_child(all);
			ft_putstr_fd("WriteOnMe: exit: too many arguments\n", 2);
			all->error_code = 1;
			return ;
		}
	}
	else
	{
		im_a_child(all);
		ft_putstr_fd("WriteOnMe: exit: ", 2);
		ft_putstr_fd(all->pipe.cmd_args[all->pipe.pipe][1], 2);
		ft_exit(": numeric argument required ARGS\n", all, 2);
	}
}

static long long int	ft_atolli(char *s)
{
	int				i;
	int				sign;
	long long int	result;

	i = 0;
	sign = 1;
	result = 0;
	if (!s)
		return (0);
	while (s[i] == ' ' || (s[i] >= 9 && s[i] <= 13))
		i++;
	if (s[i] == '-' || s[i] == '+')
	{
		if (s[i] == '-')
			sign = sign * -1;
		i++;
	}
	while (s[i] >= '0' && s[i] <= '9')
	{
		result = result * 10 + (s[i] - '0');
		i++;
	}
	return (result * sign);
}

int	do_exit(t_all *all)
{
	int long long	arg1;
	char			**arg;

	arg = all->pipe.cmd_args[all->pipe.pipe];
	if (!arg[1] && all->pipe.nb_pipe == 0)
	{
		return (ft_putstr_fd("exit\n", 2), ft_exit("", all, all->error_code),
			all->error_code);
	}
	if (!arg[1] && all->pipe.nb_pipe != 0)
		return (ft_exit("", all, all->error_code), all->error_code);
	if (ft_str_digit(arg[1]) != 0 || is_long_long(all, arg[1]) != 0)
	{
		im_a_child(all);
		ft_putstr_fd("WriteOnMe: exit: ", 2);
		ft_putstr_fd(arg[1], 2);
		ft_exit(": numeric argument required\n", all, 2);
	}
	if (arg[1] && arg[2])
		return (exit_args(all), 1);
	arg1 = ft_atolli(arg[1]);
	im_a_child(all);
	ft_exit("", all, (arg1 % 256));
	return (1);
}
