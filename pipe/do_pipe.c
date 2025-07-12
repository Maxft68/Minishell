#include "../mandatory/minishell.h"

static void	open_pipe_and_fork(t_all *all)
{
	if (all->pipe.pipe < all->pipe.nb_pipe)
	{
		if (pipe(all->pipe.pipe_fd[all->pipe.pipe]) == -1)
			perror("pipe");
	}
	all->pipe.pid[all->pipe.pipe] = fork();
	if (all->pipe.pid[all->pipe.pipe] == -1)
		ft_exit("fork failed", all, 1);
}

static void	open_hd_fd(t_all *all)
{
	if (find_last_hd(all->pipe.pipe, all))
	{
		if (dup2(all->pipe.heredoc_fd[all->pipe.pipe][0], STDIN_FILENO) == -1)
			error_dup2(all, all->pipe.heredoc_fd[all->pipe.pipe][0], "dup2");
		ft_close(all, &all->pipe.heredoc_fd[all->pipe.pipe][0]);
	}
}

static void	open_redir_in(t_all *all)
{
	if (search_pipe_redir(all->pipe.pipe, REDIRECT_IN, all)
		&& !find_last_hd(all->pipe.pipe, all))
	{
		if (do_redir_fd(all) == -1)
			ft_exit("", all, 1);
	}
	else if (!search_pipe_redir(all->pipe.pipe, REDIRECT_IN, all)
		&& all->pipe.pipe != 0)
	{
		if (dup2(all->pipe.pipe_fd[all->pipe.pipe - 1][0], STDIN_FILENO) == -1)
			error_msg(all, "dup2 stdin");
	}
}

static void	open_redir_out(t_all *all)
{
	if (search_pipe_redir(all->pipe.pipe, REDIRECT_OUT, all)
		|| search_pipe_redir(all->pipe.pipe, APPEND_OUT, all))
	{
		if (do_redir_fd(all) == -1)
			ft_exit("", all, 1);
	}
	else if (all->pipe.pipe < all->pipe.nb_pipe)
	{
		if (dup2(all->pipe.pipe_fd[all->pipe.pipe][1], STDOUT_FILENO) == -1)
			error_msg(all, "dup2 stdout");
	}
}

/******************************************************************************
We fork we are in the child process
******************************************************************************/
void	do_pipe(t_all *all)
{
	open_pipe_and_fork(all);
	if (all->pipe.pid[all->pipe.pipe] == 0)
	{
		set_up_sig_exec();
		open_hd_fd(all);
		open_redir_in(all);
		open_redir_out(all);
		close_all_pipe_exit(all);
		if (all->pipe.cmd_args[all->pipe.pipe]
			&& all->pipe.cmd_args[all->pipe.pipe][0])
		{
			if (is_built_in(all) == 0)
			{
				do_built_in(all);
				ft_exit("", all, 0);
			}
			exec_cmd(all);
		}
		ft_exit("", all, 0);
	}
}
