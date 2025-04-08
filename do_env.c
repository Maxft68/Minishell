/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdsiurds <mdsiurds@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 02:48:53 by mdsiurds          #+#    #+#             */
/*   Updated: 2025/04/08 04:11:30 by mdsiurds         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_env(t_all *all, char **env)
{
	int i;
	int j;
	int v;
	char *name;
	char *name_temp;
	char *value;
	char *value_temp;
	
	i = 0;
	while(env[i])
	{
		all->data->len_name = NULL;
		all->data->len_value = NULL;
		j = 0;
		v = 0;
		while (env[i][j] != '=')
		{
			all->data->len_name++;
			j++;
			name_temp[j] = env[i][j++];
		}
		j++;
		name = gc_malloc(all, sizeof(char) * (all->data->len_name + 1));
		while (env[i][j])
		{
			all->data->len_value++;
			j++;
			value_temp[v++] = env[i][j++];
		}
		value = gc_malloc(all, sizeof(char) * (all->data->len_value + 1));
		i++;
	}
}
