/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdsiurds <mdsiurds@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 11:00:07 by mdsiurds          #+#    #+#             */
/*   Updated: 2025/07/04 18:20:37 by mdsiurds         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
void	do_cd_home(t_all *all, char *s)
{
	if (find_the_value(all, "HOME"))
	{
		s = find_the_value(all, "HOME");
		replace_or_add_env(all, "OLDPWD", ft_pwd(all));
		replace_or_add_env(all, "PWD", s);
	}
	else
	{
		printf("WriteOnMe: cd: HOME not set\n");
		s = NULL;
	}
	if (s)
		test_the_path(all, s);
	all->error_code = 1;
	copy_list(all);
	sort_list(all);
}

void	do_cd_double_dot(t_all *all)
{
	char	*new;

	new = NULL;
	if (ft_pwd(all))
	{
		new = replace_until_the_last(all, ft_pwd(all), '/');
		replace_or_add_env(all, "OLDPWD", ft_pwd(all));
		replace_or_add_env(all, "PWD", new);
	}
	if (new)
		test_the_path(all, new);
	copy_list(all);
	sort_list(all);
}

void	do_cd_minus(t_all *all)
{
	char	*old;

	if (!find_the_value(all, "OLDPWD"))
	{
		printf("WriteOnMe: cd: OLDPWD not set\n");
		if (search_env(all, "OLDPWD"))
		{
			replace_or_add_env(all, "OLDPWD", ft_pwd(all));
			replace_or_add_env(all, "PWD", ft_pwd(all));
		}
		return ;
	}
	else
	{
		old = find_the_value(all, "OLDPWD");
		replace_or_add_env(all, "OLDPWD", ft_pwd(all));
		replace_or_add_env(all, "PWD", old);
	}
	if (old)
		test_the_path(all, old);
	copy_list(all);
	sort_list(all);
}

void	do_cd(t_all *all)
{
	char	*s;

	s = NULL;
	if (all->pipe.cmd_args[all->pipe.nb_pipe][1]
		&& all->pipe.cmd_args[all->pipe.nb_pipe][2])
	{
		printf("WriteOnMe: cd: too many arguments\n");
		all->error_code = 123456789; // test
		return ;
	}
	if (all->pipe.cmd_args[all->pipe.nb_pipe][1])
		s = all->pipe.cmd_args[all->pipe.nb_pipe][1];
	if (!s || ft_strcmp(s, "~") == 0)
		do_cd_home(all, s);
	else if (ft_strcmp(s, "-") == 0)
		do_cd_minus(all);
	else if (ft_strcmp(s, "..") == 0)
		do_cd_double_dot(all);
	else
		test_the_path(all, s);
	//all->error_code = 0;
}
