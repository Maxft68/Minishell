#include "minishell.h"

char	*gc_strjoin(t_all *all, char *s1, char *s2)
{
	int		i;
	int		j;
	char	*s1s2;

	if (!s1 || !s2)
		return (NULL);
	s1s2 = (char *)gc_malloc(all, (ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!s1s2)
		ft_exit("Cannot allocate memory\n", all, 12);
	i = 0;
	j = 0;
	while (s1[i])
	{
		s1s2[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		s1s2[i++] = s2[j];
		j++;
	}
	s1s2[i] = '\0';
	return (s1s2);
}

char	*gc_strjoin3(char *s1, char *s2, char *s3, t_all *all)
{
	char	*s4;
	char	*s5;

	s4 = gc_strjoin(all, s1, s2);
	if (!s4)
		ft_exit("Cannot allocate memory\n", all, 12);
	s5 = gc_strjoin(all, s4, s3);
	if (!s5)
		ft_exit("Cannot allocate memory\n", all, 12);
	//free(s4);
	return (s5);
}
