
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

void	close_all_pipe_exit(t_all *all) // close des pipes
{
	int i;

	i = 0;
	while (i < all->pipe.i) // quand pipe 4++ fermer pipe 1-2++
	{
		if (all->pipe.pipe_fd && all->pipe.pipe_fd[i])
		{
			close(all->pipe.pipe_fd[i][0]);
			close(all->pipe.pipe_fd[i][1]);
		}
		i++;
	}
}

void	ft_exit(char *error, t_all *all, int error_code)
{
	close_all_pipe_exit(all);
	if (error)
		ft_putstr_fd(error, 2);
	if (error_code) // useless ??
		all->error_code = error_code;
	if (!error_code) // useless  bis??
		error_code = all->error_code;
	
	if (all->rdir_tkn)
		ft_lstclear(&all->rdir_tkn);
	if (all->garbage_env)
		free_garbage_env(&all->garbage_env);
	if (all->garbage)
		free_garbage_collect(&all->garbage);
	if (all->token)
		ft_lstclear(&all->token);
	rl_clear_history();
	exit(error_code);
}

//echo 123$USER,$PWD,456
//echo 123$USER,$USER456,$USER coucou$
//echo 123$USERy,$USER456



