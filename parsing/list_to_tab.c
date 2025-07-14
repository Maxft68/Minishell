#include "../mandatory/minishell.h"

char	*gc_strdup_input(char *s, t_all *all)
{
	char	*alloc;
	size_t	l;

	if (!s)
		return (NULL);
	l = ft_strlen(s);
	alloc = gc_malloc(all, (l + 1) * sizeof(char));
	ft_strlcpy(alloc, s, l + 1);
	free(s);
	return (alloc);
}

char	*gc_strdup(char *s, t_all *all)
{
	char	*alloc;
	size_t	l;

	if (!s)
		return (NULL);
	l = ft_strlen(s);
	alloc = gc_malloc(all, (l + 1) * sizeof(char));
	ft_strlcpy(alloc, s, l + 1);
	return (alloc);
}

void	alloc_tab_star_star(t_all *all)
{
	int		i;
	int		j;
	t_token	*tmp;

	tmp = all->token;
	i = 0;
	j = 0;
	while (tmp)
	{
		if (tmp && tmp->type > 0 && tmp->type != 7)
			j++;
		if (tmp->type == PIPE || tmp->next == NULL)
		{
			all->pipe.cmd_args[i] = gc_malloc(all, (sizeof(char *) * (j + 1)));
			all->pipe.cmd_args[i][j] = NULL;
			i++;
			j = 0;
		}
		tmp = tmp->next;
	}
}

void	alloc_tab_star_star_star(t_all *all)
{
	int		i;
	t_token	*tmp;

	i = 0;
	tmp = all->token;
	while (tmp)
	{
		if (tmp->type == PIPE)
			i++;
		tmp = tmp->next;
	}
	all->pipe.cmd_args = gc_malloc(all, (sizeof(char **) * (i + 2)));
	all->pipe.cmd_args[i + 1] = NULL;
	alloc_tab_star_star(all);
}

void	list_to_tab(t_all *all)
{
	int		i;
	int		j;
	t_token	*tmp;

	i = 0;
	j = 0;
	tmp = all->token;
	alloc_tab_star_star_star(all);
	while (tmp)
	{
		if (tmp->type == PIPE)
		{
			all->pipe.cmd_args[i][j] = NULL;
			i++;
			j = 0;
		}
		if (tmp && tmp->type > 2 && tmp->type < 7)
		{
			all->pipe.cmd_args[i][j] = gc_strdup(tmp->str, all);
			j++;
		}
		tmp = tmp->next;
	}
	all->pipe.cmd_args[i][j] = NULL;
}
