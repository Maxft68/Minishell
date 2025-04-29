/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbier <rbier@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 17:55:27 by mdsiurds          #+#    #+#             */
/*   Updated: 2025/04/29 16:42:37 by rbier            ###   ########.fr       */
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
	array = NULL;
	return ;
}

void	ft_exit(char *error, t_all *all, int error_code)
{
	if (error)
		ft_putstr_fd(error, 2);
	
	free_env(&all->env);
	free_garbage_collect(&all->garbage);
	rl_clear_history();
	exit(error_code);
}
