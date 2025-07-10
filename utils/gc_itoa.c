#include "minishell.h"

static char	*special_n(t_all *all, int n)
{
	char	*s;

	s = "";
	if (n == -2147483648)
	{
		s = gc_malloc(all, 12 * sizeof(char));
		ft_strlcpy(s, "-2147483648", 12);
		return (s);
	}
	s = gc_malloc(all, 2 * sizeof(char));
	ft_strlcpy(s, "0", 2);
	return (s);
}

static int	count_char(int n)
{
	int	j;
	int	new;

	j = 0;
	new = n;
	while (new != 0)
	{
		new = new / 10;
		j++;
	}
	return (j);
}

static int	to_minus(int *n)
{
	*n *= -1;
	return (1);
}

char	*gc_itoa(t_all *all, int n)
{
	int		index[3];
	char	*s;

	index[2] = 0;
	if (n == -2147483648 || n == 0)
		return (special_n(all, n));
	index[0] = 0;
	if (n < 0)
		index[2] = to_minus(&n);
	index[0] = count_char(n);
	s = gc_malloc(all, (index[0] + 1 + index[2]) * sizeof(char));
	index[1] = (index[0] + index[2]) - 1;
	while (index[1] >= 0 + index[2])
	{
		s[index[1]] = n % 10 + '0';
		n /= 10;
		index[1] -= 1;
	}
	if (index[2] == 1)
		s[0] = '-';
	s[index[0] + index[2]] = '\0';
	return (s);
}
