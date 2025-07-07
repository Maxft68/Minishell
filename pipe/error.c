#include "../mandatory/minishell.h"

void	error_msg(t_all *all, char *s)
{
	ft_putstr_fd("WriteOnMe: ", 2);
	perror(s);
	ft_exit("", all, 1);//sauf si built-in dans parent NI EXECVE
}

int	error_msg_no_pipe(t_all *all, char *s)
{
	ft_putstr_fd("WriteOnMe: ", 2);
	all->error_code = 1;
	perror(s);
	return(1);
}

int	error_dup2(t_all *all, int fd, char *redir)
{
	close(fd);
	error_msg(all, redir);
	return(1);
} 

int	error_dup2_no_pipe(t_all *all, int fd, char *redir)
{
	close(fd);
	error_msg_no_pipe(all, redir);
	return(1);
}
