/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdsiurds <mdsiurds@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 02:48:53 by mdsiurds          #+#    #+#             */
/*   Updated: 2025/04/17 22:08:55 by mdsiurds         ###   ########.fr       */
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
		all->data.name[i] = env[i];
		i++;
	}
	all->data.name[i] = '\0';
	i++;
	while (env[i])
	{
		all->data.value[j] = env[i];
		j++;
		i++;
	}
	all->data.value[j] = '\0';
}

void	do_env(t_all *all, char **env)
{
	int	i;
	int	j;

	i = 0;
	while (env[i])
	{
		j = 0;
		all->data.len_name = 0;
		all->data.len_value = 0;
		while (env[i][j++] != '=')
			all->data.len_name++;
		all->data.name = malloc(sizeof(char) * (all->data.len_name + 1));
		if (!all->data.name)
			ft_exit("malloc fail", all, 1);
		while (env[i][j++])
			all->data.len_value++;
		all->data.value = malloc(sizeof(char) * (all->data.len_value + 1));
		if (!all->data.value)
			ft_exit("malloc fail", all, 1);
		split_env(all, env[i]);
		ft_lstadd_back_env(&all->env, ft_lstnew_env(all, all->data.name,
				all->data.value));
		i++;
	}
}
void	print_node_env(t_env *env)
{
	if (!env)
		return ;
	while (env)
	{
		printf("%s=", env->name);
		printf("%s\n", env->value);
		env = env->next;
	}
}

void	free_env(t_env **env)
{
	t_env	*temp;

	if (!env || !*env)
		return ;
	while (*env)
	{
		temp = (*env)->next;
		free((*env)->name);
		free((*env)->value);
		free(*env);
		*env = temp;
	}
}
