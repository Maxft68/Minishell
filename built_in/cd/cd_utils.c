/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdsiurds <mdsiurds@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 10:40:24 by mdsiurds          #+#    #+#             */
/*   Updated: 2025/06/27 11:01:35 by mdsiurds         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


void	test_the_path(t_all *all, char *s)
{
	char	*str;

	if (s)
	{
		str = gc_strjoin(all, "WriteOnMe: cd ", s);
		if (chdir(s) == -1)
			perror(str);
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

