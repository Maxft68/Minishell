#include "../mandatory/minishell.h"

void	alloc_my_pipe_fd(t_all *all)
{
	int	i;

	i = 0;
	if (all->pipe.nb_pipe == 0)
		return ;
	all->pipe.pipe_fd = (int **)gc_malloc(all, sizeof(int *)
			* all->pipe.nb_pipe);
	while (i < all->pipe.nb_pipe)
	{
		all->pipe.pipe_fd[i] = (int *)gc_malloc(all, sizeof(int) * 2);
		all->pipe.pipe_fd[i][0] = -1;
		all->pipe.pipe_fd[i][1] = -1;
		i++;
	}
}

void	initialise_exec(t_all *all)
{
	all->exec.i = 0;
	all->exec.j = 0;
}

void	alloc_my_herdoc_fd(t_all *all)
{
	initialise_exec(all);
	all->pipe.heredoc_fd = (int **)gc_malloc(all, sizeof(int *)
			* (all->pipe.nb_pipe + 1));
	while (all->exec.i < all->pipe.nb_pipe + 1)
	{
		all->pipe.heredoc_fd[all->exec.i] = (int *)gc_malloc(all, sizeof(int)
				* 2);
		all->pipe.heredoc_fd[all->exec.i][0] = -1;
		all->pipe.heredoc_fd[all->exec.i][1] = -1;
		all->exec.i++;
	}
	while (all->exec.j < all->pipe.nb_pipe + 1)
	{
		if (find_last_hd(all->exec.j, all))
		{
			if (pipe(all->pipe.heredoc_fd[all->exec.j]) == -1)
				error_msg(all, "pipe");
			ft_putstr_fd(find_last_hd(all->exec.j, all),
				all->pipe.heredoc_fd[all->exec.j][1]);
			ft_close(all, &all->pipe.heredoc_fd[all->exec.j][1]);
			all->pipe.heredoc_fd[all->exec.j][1] = -1;
		}
		all->exec.j++;
	}
}
