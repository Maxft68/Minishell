#include "../mandatory/minishell.h"

void	alloc_my_pipe_fd(t_all *all)
{
	int i = 0;

	if (all->pipe.nb_pipe == 0)
		return ;
	all->pipe.pipe_fd = (int **)gc_malloc(all, sizeof(int *) * all->pipe.nb_pipe);
	while (i < all->pipe.nb_pipe)
	{
		all->pipe.pipe_fd[i] = (int *)gc_malloc(all, sizeof(int) * 2);
		all->pipe.pipe_fd[i][0] = -1;
		all->pipe.pipe_fd[i][1] = -1;
		i++;
	}
}
void	alloc_my_herdoc_fd(t_all *all)
{
	if (!find_last_hd(all->pipe.pipe, all))
	{
		printf("cest la merdeee\n");
		return;
	}
	int i = 0;

	all->pipe.heredoc_fd = (int **)gc_malloc(all, sizeof(int *) * (all->pipe.nb_pipe + 1));
	while (i < all->pipe.nb_pipe + 1)
	{
		all->pipe.heredoc_fd[i] = (int *)gc_malloc(all, sizeof(int) * 2);
		all->pipe.heredoc_fd[i][0] = -1;
		all->pipe.heredoc_fd[i][1] = -1;
		i++;
	}
	i = 0;
	while(i < all->pipe.nb_pipe + 1) // pour les herdoc avant de fork
	{
		if (!find_last_hd(all->pipe.pipe, all))
		{
			if (pipe(all->pipe.heredoc_fd[i]) == -1)
			{
				perror("pipe");
			}
			ft_putstr_fd(find_last_hd(all->pipe.pipe, all), all->pipe.heredoc_fd[i][1]);
			close(all->pipe.heredoc_fd[i][1]);
			break;
		}
		i++;
	}
}

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

int	do_redir_in_no_pipe(t_all *all, char *redir)
{
	//ft_putstr_fd("--------je suis dans redir IN\n", 2);
	all->pipe.fd_infile = open(redir, O_RDONLY);
	if (all->pipe.fd_infile == -1)
		return(error_msg_no_pipe(redir));
	if (dup2(all->pipe.fd_infile, STDIN_FILENO) == -1)
		return(error_dup2_no_pipe(all->pipe.fd_infile, redir));
	if (close(all->pipe.fd_infile) == -1)
		return(error_msg_no_pipe(redir));
	return(0);
}

int	do_redir_in(t_all *all, char *redir)
{
	//ft_putstr_fd("--------je suis dans redir IN\n", 2);
	all->pipe.fd_infile = open(redir, O_RDONLY);
	if (all->pipe.fd_infile == -1)
		return(error_msg(all, redir), 1);
	if (dup2(all->pipe.fd_infile, STDIN_FILENO) == -1)
		return(error_dup2(all, all->pipe.fd_infile, redir));
	if (close(all->pipe.fd_infile) == -1)
		return(error_dup2(all, all->pipe.fd_infile, redir));
	return(0);
}

int	do_redir_fd(t_all *all)
{
	t_token *temp;

	temp = all->rdir_tkn;
	while(temp && temp->pipe != all->pipe.pipe)
		temp = temp->next;
	while(temp && temp->pipe == all->pipe.pipe)
	{
		if (temp->type == REDIRECT_IN) // mettre tout dans le meme if pour 25lignes
		{
			if (do_redir_in(all, temp->next->str) != 0)
				return (1);
			temp = temp->next->next;
		}
		else if (temp->type == REDIRECT_OUT || temp->type == APPEND_OUT)
		{
			if (temp->type == REDIRECT_OUT)
				all->pipe.fd_outfile = open(temp->next->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			else
				all->pipe.fd_outfile = open(temp->next->str, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (all->pipe.fd_outfile == -1)
				return (error_msg(all, temp->next->str), 1);
			if (dup2(all->pipe.fd_outfile, STDOUT_FILENO) == -1)
				return(error_dup2(all, all->pipe.fd_outfile, temp->next->str), 1);
			if (close(all->pipe.fd_outfile) == -1)
				return (error_msg(all, temp->next->str), 1);
			temp = temp->next->next;
		}
		else
			temp = temp->next;
	}
	return(0);
}

int	do_redir_no_pipe(t_all *all)
{
	t_token *temp;

	temp = all->rdir_tkn;
	while(temp && temp->pipe != all->pipe.pipe)
		temp = temp->next;
	while(temp && temp->pipe == all->pipe.pipe)
	{
		// if (is_herdoc(all->pipe.pipe)) // a modifier quqnd jaurais la vrai fonction et a ne ps appeler plusieurs fois...
		// {
		// 	if(dup2(all->pipe.heredoc_fd[all->pipe.pipe][0], STDIN_FILENO) == -1)
		// 		error_dup2(all, all->pipe.heredoc_fd[all->pipe.pipe][0], "dup2");
		// }
		if (temp->type == REDIRECT_IN) //else if
		{
			if(do_redir_in_no_pipe(all, temp->next->str) == 1)
				return(1);
			temp = temp->next->next;
		}
		else if (temp->type == REDIRECT_OUT || temp->type == APPEND_OUT)
		{
			if (temp->type == REDIRECT_OUT)
				all->pipe.fd_outfile = open(temp->next->str, O_WRONLY | O_CREAT | O_TRUNC, 0644); // a checker le 0644
			else
				all->pipe.fd_outfile = open(temp->next->str, O_WRONLY | O_CREAT | O_APPEND, 0644); // a checker le 0644
			if (all->pipe.fd_outfile == -1)
				return(error_msg_no_pipe(temp->next->str));
			if (dup2(all->pipe.fd_outfile, STDOUT_FILENO) == -1)
				return(error_dup2_no_pipe(all->pipe.fd_outfile, temp->next->str));
			if (close(all->pipe.fd_outfile) == -1)
				return(error_msg_no_pipe(temp->next->str));
			temp = temp->next->next;
		}
		else
			temp = temp->next;
	}
	return(0);
}


int	do_no_pipe(t_all *all)
{
	int stdout_original = dup(STDOUT_FILENO);
	int stdin_original = dup(STDIN_FILENO);
	if(do_redir_no_pipe(all) == 1 || !all->pipe.cmd_args[0][0])
		return(dup2(stdout_original, STDOUT_FILENO), dup2(stdin_original, STDIN_FILENO), close (stdout_original), close (stdin_original), 1);
	do_built_in(all);
	dup2(stdout_original, STDOUT_FILENO);
	dup2(stdin_original, STDIN_FILENO);
	close (stdout_original);
	close (stdin_original);
	
	//printf("j'exit apres mon built in / PAS DE PIPE \n");
	return(0);
}

void	do_pipe(t_all *all) //dans process enfant faire exit(1) pas ft_exit 
{ //(lenfant le fait lui meme)
	if (all->pipe.pipe < all->pipe.nb_pipe)
	{
		if (pipe(all->pipe.pipe_fd[all->pipe.pipe]) == -1)
			perror("pipe");
	}
	all->pipe.pid[all->pipe.pipe] = fork();				// ---------FORK ICI
	if (all->pipe.pid[all->pipe.pipe] == -1)
		ft_exit("fork failed", all, 1);
	if (all->pipe.pid[all->pipe.pipe] == 0)
	{
		ft_putstr_fd("\n----------------------Pipeline ", 2);
		ft_putnbr_fd(all->pipe.pipe, 2);
		ft_putstr_fd(" -----------------------PIPE et je suis dans do pipe\n", 2);

		// if (is_heredoc(all->pipe.pipe))
		// {
		// 	if(dup2(all->pipe.heredoc_fd[all->pipe.pipe][0], STDIN_FILENO) == -1)
		// 		error_dup2(all, all->pipe.heredoc_fd[all->pipe.pipe][0], "dup2");
		// }
		if (search_pipe_redir(all->pipe.pipe, REDIRECT_IN, all))//|| search_pipe_redir(all->pipe.pipe, HEREDOC, all)
		{
			ft_putstr_fd("RENTRE ICI PLZ IL Y A REDIRECTION IN\n", 2);
			if (do_redir_fd(all) == -1)
				ft_exit("", all, 1);//sauf si built-in dans parent //si un infile foire ou un out alors fail = -1
		}
		else if (!search_pipe_redir(all->pipe.pipe, REDIRECT_IN, all) && all->pipe.pipe != 0)
		{
			ft_putstr_fd("REDIRECTION IN du pipe precedent\n", 2);
			if (dup2(all->pipe.pipe_fd[all->pipe.pipe - 1][0], STDIN_FILENO) == -1)
				error_msg(all, "dup2 stdin");
		}
		if (search_pipe_redir(all->pipe.pipe, REDIRECT_OUT, all) || 
			search_pipe_redir(all->pipe.pipe, APPEND_OUT, all)) //si au moins une redir alors faire redir
		{
			ft_putstr_fd("RENTRE ICI PLZ IL Y A REDIRECTION OUT\n", 2);
			if (do_redir_fd(all) == -1)
				ft_exit("", all, 1);//sauf si built-in dans parent //si un infile foire ou un out alors fail = -1
		}
		else if (all->pipe.pipe < all->pipe.nb_pipe) // derniere commande
		{
			ft_putstr_fd("REDIRECTION OUT dans pipe depuis le pipeline numero ", 2);
			ft_putnbr_fd(all->pipe.pipe, 2);
			ft_putstr_fd(" derniere commande\n", 2);
			if (dup2(all->pipe.pipe_fd[all->pipe.pipe][1], STDOUT_FILENO) == -1)
				error_msg(all, "dup2 stdout");
		}
		int j = 0;
		while (j < all->pipe.nb_pipe)
		{
			if (all->pipe.pipe_fd[j][0] != -1)
				close(all->pipe.pipe_fd[j][0]);
			if (all->pipe.pipe_fd[j][1] != -1)
				close(all->pipe.pipe_fd[j][1]);
			j++;
		}
		if (all->pipe.cmd_args[all->pipe.pipe] && all->pipe.cmd_args[all->pipe.pipe][0])
		{
			if (is_built_in(all) == 0)
			{
				do_built_in(all);
				ft_exit("test", all, 1);
			}
			else
			{
				ft_putstr_fd("je vais execve\n", 2);
				exec_cmd(all);
			}
		}
		ft_putstr_fd("JAI PAS EXECVE\n", 2);
		ft_exit("test", all, 1);
	}
}

// echo nouveau1 >out1 | echo nouveau21 | cat | cat >out2 | echo nouveau31 | cat
//   echo a >out1 | echo b > out2 | >out3 echo c | > out4 echo d | echo e                     TEST IN

int	exec_part(t_all *all)
{
	int status;
	all->pipe.pid = gc_malloc(all, sizeof(pid_t) * (all->pipe.nb_pipe + 1)); //sizeof(int *)
	alloc_my_pipe_fd(all);
	//alloc_my_herdoc_fd(all);
	int i;

	i = 0; 
	while(i < all->pipe.nb_pipe + 1) //exec dans enfant
	{
		if (all->pipe.nb_pipe < 1 && (is_built_in(all) == 0 || !all->pipe.cmd_args[0][0]))
		{
			ft_putstr_fd("je rentre dans no pipe, pipeline =", 2);
			ft_putnbr_fd(all->pipe.pipe, 2);
			ft_putstr_fd(" \n", 2);
			if (do_no_pipe(all) == 1)
				return(1);
			return(0);
		}
		else
		{
			ft_putstr_fd("je rentre dans do_pipe, pipeline = ", 2);
			ft_putnbr_fd(all->pipe.pipe, 2);
			ft_putstr_fd(" \n", 2);

			do_pipe(all); //fork la dedans
		}
		if (i < all->pipe.nb_pipe)
		{
			close(all->pipe.pipe_fd[i][1]);
			all->pipe.pipe_fd[i][1] = -1;
		}
		if (i > 0 && all->pipe.pipe_fd[i - 1][0] != -1)
		{
			close(all->pipe.pipe_fd[i - 1][0]);
			all->pipe.pipe_fd[i - 1][0] = -1;
		}
        if (all->pipe.heredoc_fd && all->pipe.heredoc_fd[all->pipe.pipe][0] != -1)
        {
            close(all->pipe.heredoc_fd[all->pipe.pipe][0]);
            all->pipe.heredoc_fd[all->pipe.pipe][0] = -1;
        }
		
		

		i++;
		//printf("i =%d\n", i);
		all->pipe.pipe++;
		// close_pipe(all);
		// if(!(i < all->pipe.nb_pipe + 1))
		// 	close_all_pipe_exit(all);
	}
	i = 0;
	all->pipe.pipe = 0;
	while (i < all->pipe.nb_pipe + 1)
	{
		if (waitpid(all->pipe.pid[i], &status, 0) == -1) //&status pour le code erreur a rajouter plus tard
			ft_exit("WAITPID", all, 1);
		// if (i == all->pipe.nb_pipe - 1)
		// 	//signaux(status ...)
		// else
		// 	//signaux(status.....)
		i++;
	}
	all->pipe.i = 0;
	all->pipe.pipe = 0;
	all->pipe.nb_pipe = 0;
	return(0);
}



