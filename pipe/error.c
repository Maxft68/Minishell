#include "../mandatory/minishell.h"

void	error_msg(t_all *all, char *s)
{
	ft_putstr_fd("WriteOnMe: ", 2);
	perror(s); //a verifier si \n ou pas
	ft_exit("", all, 1);//sauf si built-in dans parent NI EXECVE
}

int	error_msg_no_pipe(char *s)
{
	ft_putstr_fd("WriteOnMe: ", 2);
	perror(s); //a verifier si \n ou pas
	return(1);
}

int	error_dup2(t_all *all, int fd, char *redir)
{
	ft_putstr_fd("NTR", 2);
	close(fd);
	error_msg(all, redir);
	return(1);
} 

int	error_dup2_no_pipe(int fd, char *redir)
{
	error_msg_no_pipe(redir);
	close(fd);
	return(1);
}
