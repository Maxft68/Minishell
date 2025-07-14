
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

void	close_all_pipe_exit(t_all *all)
{
	int i;

	i = 0;
	while (i < all->pipe.nb_pipe)
	{
		if (all->pipe.heredoc_fd && all->pipe.heredoc_fd[i])
		{
			if (all->pipe.heredoc_fd[i][0] != -1)
				ft_close(all, &all->pipe.heredoc_fd[i][0]);
			if (all->pipe.heredoc_fd[i][1] != -1)
				ft_close(all, &all->pipe.heredoc_fd[i][1]);
		}
		if (all->pipe.pipe_fd && all->pipe.pipe_fd[i])
		{
			if (all->pipe.pipe_fd[i][0] != -1)
				ft_close(all, &all->pipe.pipe_fd[i][0]);
			if (all->pipe.pipe_fd[i][1] != -1)
				ft_close(all, &all->pipe.pipe_fd[i][1]);
		}
		i++;
	}
}

void	ft_exit(char *error, t_all *all, int error_code)
{
	close_all_pipe_exit(all);
	if (error)
		ft_putstr_fd(error, 2);
	if (error_code)
		all->error_code = error_code;
	if (all->garbage)
		free_garbage_collect(&all->garbage);
	if (all->garbage_env)
		free_garbage_env(&all->garbage_env);
	rl_clear_history();
	exit(error_code);
}
