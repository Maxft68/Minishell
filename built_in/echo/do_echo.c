/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdsiurds <mdsiurds@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 20:43:35 by mdsiurds          #+#    #+#             */
/*   Updated: 2025/04/17 22:10:05 by mdsiurds         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "minishell.h"

# include <limits.h> 
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
//test git
void	ft_putchar_fd(char c, int fd)
{
	if (fd < 0)
		return ;
	write(fd, &c, 1);
}

void	do_echo(char *str, int fd)
{
	int	i;
	int	argument_n;

	argument_n = 0;
	i = 0;
	if (!str)
		ft_putchar_fd('\n', fd);
	while (str[i])
	{
		if (i == 0 && str[i] == '-' && str[i + 1] == 'n')
		{
			i += 2;
			argument_n = 1;
			while (str[i] == 'n')
				i++;
		}
		ft_putchar_fd(str[i], fd);
		i++;
	}
	if (argument_n == 0)
		ft_putchar_fd('\n', fd);
}
// gerer le -nnnnnnnnnnnnnnn

int main()
{
	char *str = "-nnnnnntnnn -n       -n coucou marc"; "-nnnnnntnnn -n       -n coucou marc" 
	ca doit renvoyer "-nnnnnntnnn -n       -n coucou marc"
	do_echo(str, 1);
}