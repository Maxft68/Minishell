#include "../mandatory/minishell.h"

/******************************************************************************
Redirection of the last heredoc in the pipe to stdin in child process
******************************************************************************/
void	do_hd_fd(t_all *all)
{
	if (find_last_hd(all->pipe.pipe, all))
	{
		if (dup2(all->pipe.heredoc_fd[all->pipe.pipe][0], STDIN_FILENO) == -1)
			error_dup2(all, all->pipe.heredoc_fd[all->pipe.pipe][0], "dup2");
	}
}

/******************************************************************************
Redirection of file descriptors from char *infile to stdin in child process
******************************************************************************/
int	do_redir_in(t_all *all, char *redir)
{
	// ft_putstr_fd("--------je suis dans redir IN\n", 2);
	all->pipe.fd_infile = open(redir, O_RDONLY);
	if (all->pipe.fd_infile == -1)
		return (error_msg(all, redir), 1);
	if (dup2(all->pipe.fd_infile, STDIN_FILENO) == -1)
		return (error_dup2(all, all->pipe.fd_infile, redir));
	ft_close(all, &all->pipe.fd_infile);
	return (0);
}

int	do_redir_out(t_all *all, char *temp, t_token_type type)
{
	if (type == REDIRECT_OUT)
		all->pipe.fd_outfile = open(temp, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		all->pipe.fd_outfile = open(temp, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (all->pipe.fd_outfile == -1)
		return (error_msg(all, temp), 1);
	if (dup2(all->pipe.fd_outfile, STDOUT_FILENO) == -1)
		return (error_dup2(all, all->pipe.fd_outfile, temp), 1);
	ft_close(all, &all->pipe.fd_outfile);
	return (0);
}

/******************************************************************************
Redirection of file descriptors for input and output
******************************************************************************/
int	do_redir_fd(t_all *all)
{
	t_token	*temp;

	temp = all->rdir_tkn;
	while (temp && temp->pipe != all->pipe.pipe)
		temp = temp->next;
	do_hd_fd(all);
	while (temp && temp->pipe == all->pipe.pipe)
	{
		if (temp->type == REDIRECT_IN)
		{
			if (do_redir_in(all, temp->next->str) != 0)
				return (1);
			temp = temp->next->next;
		}
		else if (temp->type == REDIRECT_OUT || temp->type == APPEND_OUT)
		{
			if (do_redir_out(all, temp->next->str, temp->type) == 1)
				return (1);
			temp = temp->next->next;
		}
		else
			temp = temp->next;
	}
	return (0);
}
void	close_fd_and_hd_fd(t_all *all, int i)
{
	if (i < all->pipe.nb_pipe)
	{
		ft_close(all, &all->pipe.pipe_fd[i][1]);
		all->pipe.pipe_fd[i][1] = -1;
	}
	if (i > 0 && all->pipe.pipe_fd[i - 1][0] != -1)
	{
		ft_close(all, &all->pipe.pipe_fd[i - 1][0]);
		all->pipe.pipe_fd[i - 1][0] = -1;
	}
	if (all->pipe.heredoc_fd && all->pipe.heredoc_fd[all->pipe.pipe][0] != -1)
	{
		ft_close(all, &all->pipe.heredoc_fd[all->pipe.pipe][0]);
		all->pipe.heredoc_fd[all->pipe.pipe][0] = -1;
	}
}
