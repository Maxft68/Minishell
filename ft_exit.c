/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdsiurds <mdsiurds@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 22:02:45 by mdsiurds          #+#    #+#             */
/*   Updated: 2025/04/07 19:32:56 by mdsiurds         ###   ########.fr       */
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

static void	garbage_collect(t_all *all)
{
	(void)all;
}

void	ft_exit(char *error, t_all *all, int error_code)
{
	ft_putstr_fd(error, 2);
	garbage_collect(all);
	rl_clear_history();
	exit(error_code);
}
