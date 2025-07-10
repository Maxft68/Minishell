/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbier <rbier@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 10:40:24 by mdsiurds          #+#    #+#             */
/*   Updated: 2025/07/10 23:58:43 by rbier            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../mandatory/minishell.h"

void	test_the_path_mini(t_all *all, char *s)
{
	char	*str;
	char	*temp;
	int i = ft_strlen(s);
	while (i > 0 && (s[i - 1] == '/'))
	{
		temp = gc_substr_env(s, 0, i - 1, all);
		s = temp;
		i--;
	}
	if(chdir(s) == -1)
		{
			str = gc_strjoin(all, "WriteOnMe: cd ", s);
			perror(str);
			all->error_code = 1;
		}
}

void	test_the_path(t_all *all, char *s)
{
	char	*str;

	if (s)
	{
		str = ft_pwd(all);
		if (!str || s[0] == '\0')
			return ;
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

	//printf("ancien s=%s\n", s);
	s = do_valid_s(all, s);
	//printf("nouveau s=%s\n", s);
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
