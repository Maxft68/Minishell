/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdsiurds <mdsiurds@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 10:40:24 by mdsiurds          #+#    #+#             */
/*   Updated: 2025/07/05 15:32:00 by mdsiurds         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
void	test_the_path(t_all *all, char *s)
{
	char	*str;

	if (s)
	{
		str = find_the_value(all, "PWD"); // copy
		if (s[0] == '/' && chdir(s) == 0)
		{
			replace_or_add_env(all, "OLDPWD", gc_strdup_env(str, all));
			replace_or_add_env(all, "PWD", gc_strdup_env(s, all));
		}
		else if (chdir(s) == 0)
		{
			replace_or_add_env(all, "OLDPWD", gc_strdup_env(str, all));
			replace_or_add_env(all, "PWD", gc_strjoin_env(all, find_the_value(all, "PWD"), "/"));
			replace_or_add_env(all, "PWD", gc_strjoin_env(all, find_the_value(all, "PWD"), s));
		}
		else if(chdir(s) == -1)
		{
			str = gc_strjoin(all, "WriteOnMe: cd ", s);
			perror(str);
			all->error_code = 1;
		}
	}
	
}

char	*replace_until_the_last(t_all *all, char *s, int c)
{
	size_t	i;
	int		j;
	char	*new;

	i = ft_strlen(s);
	j = i;
	while (i > 0)
	{
		if (s[i] != (char)c)
			i--;
		else
		{
			new = gc_substr_env(s, 0, j - (j - i), all);
			return (new);
		}
	}
	if (s[i] == (char)c)
		return (new = gc_substr_env(s, 0, 1, all));
	return (NULL);
}

char	*find_the_value(t_all *all, char *name)
{
	t_env *current;
	if (!all->env || !name)
		return (NULL);
	current = all->env;
	while (current)
	{
		if (ft_strcmp(current->name, name) == 0)
		{
			if (current->value)
				return (current->value);
		}
		current = current->next;
	}
	return (NULL);
}
