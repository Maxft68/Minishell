#include "../mandatory/minishell.h"

static void	get_code_error(t_all *all, int n)
{
	all->error_code = n + 128;
}

static void	update_minishell_code(t_all *all, int n)
{
	if (n >= 0 && n < 256)
		all->error_code = n;
	else if (n >= 256)
		all->error_code = n % 256;
	else
		all->error_code = (n % 256) + 256;
}

static int	pipe_or_not_pipe(t_all *all)
{
	if (all->pipe.nb_pipe < 1 && (is_built_in(all) == 0
			|| !all->pipe.cmd_args[0][0]))
	{
		if (do_no_pipe(all) == 1)
			return (1);
		return (0);
	}
	else
		do_pipe(all);
	return (0);
}

static void	waiting_zzz(t_all *all, int i, int *status)
{
	waitpid(all->pipe.pid[i], status, 0);
	if (WIFEXITED(*status))
		update_minishell_code(all, WEXITSTATUS(*status));
	else if (WIFSIGNALED(*status))
	{
		if (WTERMSIG(*status) == 2)
			printf("\n");
		get_code_error(all, WTERMSIG(*status));
	}
}

int	exec_part(t_all *all)
{
	int	status;
	int	i;

	i = 0;
	status = 0;
	all->pipe.pid = gc_malloc(all, sizeof(pid_t) * (all->pipe.nb_pipe + 1));
	memset(all->pipe.pid, 0, sizeof(pid_t) * (all->pipe.nb_pipe + 1));
	alloc_my_pipe_fd(all);
	alloc_my_herdoc_fd(all);
	while (i < all->pipe.nb_pipe + 1)
	{
		pipe_or_not_pipe(all);
		close_fd_and_hd_fd(all, i);
		i++;
		all->pipe.pipe++;
	}
	i = 0;
	all->pipe.pipe = 0;
	while (i < all->pipe.nb_pipe + 1)
		waiting_zzz(all, i++, &status);
	all->pipe.i = 0;
	all->pipe.pipe = 0;
	all->pipe.nb_pipe = 0;
	return (0);
}
