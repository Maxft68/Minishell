

#include "minishell.h"

# include <limits.h> 
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>

void	ft_putchar_fd(char c, int fd)
{
	if (fd < 0)
		return ;
	write(fd, &c, 1);
}

void	do_echo(char ***args, int pipe)
{
	int	j;
	int	argument_n;

	argument_n = 0;
	j = 1;

	if (!args[pipe] || !args[pipe][j])
	{
		ft_putchar('\n');
		return;
	}

	while (args[pipe][j] && args[pipe][j][0] == '-' && args[pipe][j][1] == 'n')
	{
		int i = 2;
		while (args[pipe][j][i] == 'n')
			i++;
		if (args[pipe][j][i] == '\0') // alors juste -nnnnnnnnnnn
		{
			argument_n = 1;
			j++;
		}
		else
			break;
	}
	while (args[pipe][j])
	{
		int i = 0;
		while (args[pipe][j][i])
		{
			ft_putchar(args[pipe][j][i]);
			i++;
		}
		j++;
		if (j > 1 && args[pipe][j] != NULL && args[pipe][j - 1][0] != '\0')
			ft_putchar(' ');
		}
		if (argument_n == 0)
		ft_putchar('\n');
	}

