#include "minishell.h"

static int	words_count(char *s, char c)
{
	int	i;
	int	nb;
	int	inorout;

	i = 0;
	nb = 0;
	inorout = 0;
	while (s[i])
	{
		if (s[i] != c && inorout == 0)
		{
			inorout = 1;
			nb++;
		}
		if (s[i] == c)
			inorout = 0;
		i++;
	}
	return (nb);
}

static char	*str_c_dup(t_all *all, char *s, int start, int end)
{
	char	*alloc;

	alloc = gc_malloc(all, (end - start + 2) * sizeof(char));
	ft_strlcpy(alloc, s + start, end - start + 2);
	return (alloc);
}

// static void	ft_free_all(char **array, int a)
// {
// 	while (a >= 0)
// 	{
// 		free(array[a]);
// 		a--;
// 	}
// 	free(array);
// }

static char	**ft_inter_split(t_all *all, char **array, char *s, char c)
{
	int	i;
	int	a;
	int	start;

	a = 0;
	i = 0;
	while (a < words_count(s, c))
	{
		while (s[i] == c)
			i++;
		start = i;
		while (s[i] != c && s[i] != 0)
			i++;
		array[a] = str_c_dup(all, s, start, i - 1);
		a++;
	}
	array[a] = NULL;
	return (array);
}

char	**gc_split(t_all *all, char *s, char c)
{
	char	**array;

	if (!s)
		return (NULL);
	array = gc_malloc(all, (words_count(s, c) + 1) * sizeof(char *));
	return (ft_inter_split(all, array, s, c));
}
