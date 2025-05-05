/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdsiurds <mdsiurds@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 20:43:35 by mdsiurds          #+#    #+#             */
/*   Updated: 2025/05/05 13:30:01 by mdsiurds         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "minishell.h"

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
// do_echo(all->pipe.cmd_args[all->pipe.pipe], fd)
// void	do_echo(char ***args, int pipe, int fd)
// {
// 	int	i;
// 	int j = 1;
// 	int	argument_n;

// 	argument_n = 0;
// 	i = 0;
	
// 	if (!args[pipe][j])
// 		ft_putchar_fd('\n', fd);
// 	while (args[pipe][j] && args[pipe][j][i])
// 	{
// 		if (i == 0 && args[pipe][j][i] == '-' && args[pipe][j][i + 1] == 'n' && argument_n == 0) // le -n forcement au debut
// 		{
// 			i += 2;
// 			argument_n = 1;
// 			while (args[pipe][j] && args[pipe][j][i] == 'n')
// 			{
// 				i++;
// 				if (args[pipe][j] && args[pipe][j][i] != 'n' && args[pipe][j][i] != ' ')
// 					i = 0;
// 			}
// 		}
// 		ft_putchar_fd(args[pipe][j][i], fd);
// 		i++;
// 	}
// 	if (argument_n == 0)
// 		ft_putchar_fd('\n', fd);
// }

void	do_echo(char ***args, int pipe, int fd)
{
	int	j;
	int	argument_n;

	argument_n = 0;
	j = 1;

	if (!args[pipe] || !args[pipe][j])
	{
		ft_putchar_fd('\n', fd);
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
			ft_putchar_fd(args[pipe][j][i], fd);
			i++;
		}
		j++;
		if (j > 1 && args[pipe][j] != NULL)
			ft_putchar_fd(' ', fd);
		}
		if (argument_n == 0)
		ft_putchar_fd('\n', fd);
	}
	
	
	// gerer le -nnnnnnnnnnnnnnn
	
	#include <stdio.h>
	int main()
{
	char ***args = malloc(2 * sizeof(char **));
	args[0] = malloc(5 * sizeof(char *));
	args[0][0] = "echo";
	args[0][1] = "";
	args[0][2] = "HELLO";
	args[0][3] = "-n";
	args[0][4] = NULL;
	
	args[1] = NULL;
	int pipe = 0;
	int fd = 1;
	//ca doit renvoyer "-nnnnnntnnn   -n       -n coucou marc" // fonctionnelle a condition
	// de recevoir les arguments sans espaces
	do_echo(args, pipe, fd);
}

//-n -n -n -nnnnnn doit fonctionner comme un simple -n
