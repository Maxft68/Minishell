/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdsiurds <mdsiurds@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 12:46:16 by mdsiurds          #+#    #+#             */
/*   Updated: 2025/04/25 18:53:01 by mdsiurds         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_export(all)
{
	

}

void	print_export(t_env *env)
{
	
	if (!env)
		return ;
	while (env)
	{
		printf ("declare -x ");
		printf ("%s=", env->name);
		printf ("\"%s\"\n", env->value);
		env = env->next;
	}
}

void	sort_tab(t_all *all)
{
	
}
