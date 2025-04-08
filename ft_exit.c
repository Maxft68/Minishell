/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdsiurds <mdsiurds@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 22:02:45 by mdsiurds          #+#    #+#             */
/*   Updated: 2025/04/08 02:27:17 by mdsiurds         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_array(char **array)
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

void	ft_exit(char *error, t_all *all, int error_code)
{
	ft_putstr_fd(error, 2);
	if (all)
	{
		free_garbage_collect(all);
		free(all);
	}
	rl_clear_history();
	exit(error_code);
}
