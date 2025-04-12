/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdsiurds <mdsiurds@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 02:48:53 by mdsiurds          #+#    #+#             */
/*   Updated: 2025/04/12 15:58:36 by mdsiurds         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	split_env(t_all *all, char *env)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (env[i] != '=')
	{
		all->data->name[i] = env[i];
		i++;
	}
	all->data->name[i] = '\0';
	i++;
	while (env[i])
	{
		all->data->value[j] = env[i];
		j++;
		i++;
	}
	all->data->value[j] = '\0';
}

void	do_env(t_all *all, char **env)
{
	int	i;
	int	j;

	i = 0;
	while (env[i])
	{
		j = 0;
		all->data->len_name = 0;
		all->data->len_value = 0;
		while (env[i][j++] != '=')
			all->data->len_name++;
		j++;
		all->data->name = malloc(sizeof(char) * (all->data->len_name + 1));
		while (env[i][j++])
			all->data->len_value++;
		all->data->value = malloc(sizeof(char) * (all->data->len_value + 1));
		split_env(all, env[i]);
		ft_lstadd_back_env(&all->env, ft_lstnew_env(all, all->data->name,
				all->data->value));
		i++;
	}
}
