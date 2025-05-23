
#include "../mandatory/minishell.h"

void	free_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array && array[i])
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	free(array);
	array = NULL;
	return ;
}

void	ft_exit(char *error, t_all *all, int error_code)
{
	if (error)
		ft_putstr_fd(error, 2);
	
	free_garbage_env(&all->garbage_env);
	free_garbage_collect(&all->garbage);
	ft_lstclear(&all->token);
	rl_clear_history();
	
	exit(error_code);
}
