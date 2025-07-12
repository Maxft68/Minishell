#include "../mandatory/minishell.h"

int	ft_close(t_all *all, int *fd)
{
	if (*fd >= 0)
	{
		if (close(*fd) == -1)
		{
			all->error_code = 1;
			ft_putstr_fd("WriteOnMe: ", 2);
			perror("close");
			*fd = -1;
			return (1);
		}
	}
	*fd = -1;
	return (0);
}

void	error_msg(t_all *all, char *s)
{
	ft_putstr_fd("WriteOnMe: ", 2);
	perror(s);
	ft_exit("", all, 1);
}

int	error_msg_no_pipe(t_all *all, char *s)
{
	ft_putstr_fd("WriteOnMe: ", 2);
	all->error_code = 1;
	perror(s);
	return (1);
}

int	error_dup2(t_all *all, int fd, char *redir)
{
	ft_close(all, &fd);
	all->error_code = 1;
	error_msg(all, redir);
	return (1);
}
