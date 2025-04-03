/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdsiurds <mdsiurds@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 22:02:45 by mdsiurds          #+#    #+#             */
/*   Updated: 2025/04/03 22:21:52 by mdsiurds         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array && array[i])
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	free(array);
	return ;
}

static void	close_all_array(t_all *all)
{
	if (all->pipe->cmd1_args)
		free_array(all->pipe->cmd1_args);
	all->pipe->cmd1_args = NULL;
}

void	ft_exit(char *error, t_all *all, int error_code)
{
	ft_putstr_fd(error, 2);
	close_all_array(all);

	exit(error_code);
}