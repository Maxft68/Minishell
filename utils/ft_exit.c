
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
	if (all->garbage_env)
		free_garbage_env(&all->garbage_env);
	if (all->garbage)
		free_garbage_collect(&all->garbage);
	if (all->token)
		ft_lstclear(&all->token);
	rl_clear_history();
	if (error_code)
		all->error_code = error_code;
	exit(error_code);
}

//echo 123$USER,$PWD,456
//echo 123$USER,$USER456,$USER coucou$
//echo 123$USERy,$USER456



