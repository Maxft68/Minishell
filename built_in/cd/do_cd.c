/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbier <rbier@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 11:00:07 by mdsiurds          #+#    #+#             */
/*   Updated: 2025/07/14 16:43:38 by rbier            ###   ########.fr       */
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
		ft_putstr_fd("WriteOnMe: cd: HOME not set\n", 2);
		s = NULL;
	}
	if (s)
		test_the_path(all, s);
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
		test_the_path_mini(all, new);
	copy_list(all);
	sort_list(all);
}

void	do_cd_minus(t_all *all)
{
	char	*old;

	if (!find_the_value(all, "OLDPWD"))
	{
		ft_putstr_fd("WriteOnMe: cd: OLDPWD not set\n", 2);
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

char	*do_valid_s(t_all *all, char *s)
{
	size_t	i;
	char	*temp;

	i = ft_strlen(s);
	while (i > 0 && (s[i - 1] == '/'))
	{
		temp = gc_substr_env(s, 0, i - 1, all);
		s = temp;
		i--;
	}
	return (s);
}

void	do_cd(t_all *all)
{
	char	*s;

	s = NULL;
	if (all->pipe.cmd_args[all->pipe.nb_pipe][1]
		&& all->pipe.cmd_args[all->pipe.nb_pipe][2])
	{
		ft_putstr_fd("WriteOnMe: cd: too many arguments\n", 2);
		all->error_code = 1;
		return ;
	}
	if (all->pipe.cmd_args[all->pipe.nb_pipe][1])
		s = do_valid_s(all, all->pipe.cmd_args[all->pipe.nb_pipe][1]);
	if (!s || ft_strcmp(s, "~") == 0)
		do_cd_home(all, s);
	else if (ft_strcmp(s, "-") == 0)
		do_cd_minus(all);
	else if (ft_strcmp(s, "..") == 0)
		do_cd_double_dot(all);
	else
		test_the_path(all, s);
}
