#include "../mandatory/minishell.h"

void	alloc_my_pipe_fd(t_all *all)
{
	int i = 0;
	all->pipe.pipe_fd = (int **)gc_malloc(all, sizeof(int *) * all->pipe.nb_pipe);
	while (i < all->pipe.nb_pipe)
	{
		all->pipe.pipe_fd[i] = (int *)gc_malloc(all, sizeof(int) * 2);
		i++;
	}
	i = 0;

	// while(i < all->pipe.nb_pipe) // pour les herdoc avant de fork
	// {
	// 	if (heredoc_in(i)) 
	// 	{
	// 		if (pipe(herdoc_fd[i]) == -1)
	// 		{
	// 			perror("pipe");
	// 			return (1);
	// 		}
	// 		ft_putstr_fd(char *mon_herdoc, herdoc_fd[i][1]);
	// 	}
	// 	i++;
	// }
}

int	do_redir_fd(t_all *all)
{
	t_token *temp;

	temp = all->rdir_tkn;
	ft_putstr_fd("-------je suis dans redir\n", 2);
	while(temp && temp->pipe != all->pipe.pipe)
		temp = temp->next;
	while(temp && temp->pipe == all->pipe.pipe) // ou pipe.pipe = pipe actuel
	{
		if (temp->type >= 6 && temp->type <= 9) // 8 et 11 apres merge et RAJOUTER && temp->next
		{

			if (temp->type == REDIRECT_IN) 
			{
				ft_putstr_fd("--------je suis dans redir IN\n", 2);
				all->pipe.fd_infile = open(temp->next->str, O_RDONLY);
				if (all->pipe.fd_infile == -1)
				{
					perror("open infile"); //a verifier si \n ou pas
					exit(1);//sauf si built-in dans parent
				}
				if (dup2(all->pipe.fd_infile, STDIN_FILENO) == -1)
				{
					perror("dup2 fd_infile");
					exit(1);//sauf si built-in dans parent
				}
				close(all->pipe.fd_infile);
			}
			// if (temp->type == HEREDOC)
			// {
			// 	all->pipe.fd_infile = ; // a checker le 0644
			// 	if (all->pipe.fd_infile == -1)
			// 	{
			// 		perror("open infile HEREDOC");
			// 		exit(1);//sauf si built-in dans parent
			// 	}
			// }
			if (temp->type == REDIRECT_OUT || temp->type == APPEND_OUT)
			{
				ft_putstr_fd("------je suis dans redir out globale\n", 2);
				if (temp->type == REDIRECT_OUT)
				{
					ft_putstr_fd("Pipeline: ", 2);
					ft_putnbr_fd(all->pipe.pipe, 2);
					ft_putstr_fd("\n------je suis dans redir out, mon out est: ", 2);
					ft_putstr_fd(temp->next->str, 2);
					ft_putstr_fd(" \n", 2);
					all->pipe.fd_outfile = open(temp->next->str, O_WRONLY | O_CREAT | O_TRUNC, 0644); // a checker le 0644
				}
				if (temp->type == APPEND_OUT)
				{
					ft_putstr_fd("------je suis dans redir APPEND OUT\n", 2);
					all->pipe.fd_outfile = open(temp->next->str, O_WRONLY | O_CREAT | O_APPEND, 0644); // a checker le 0644
				}
				if (all->pipe.fd_outfile == -1)
					{
						perror("open outfile"); //temp->str ??
						exit(1);//sauf si built-in dans parent
					}
				if (dup2(all->pipe.fd_outfile, STDOUT_FILENO) == -1)
				{
					perror("dup2 fd_outfile");
					exit(1);//sauf si built-in dans parent
				}
				close(all->pipe.fd_outfile);
			}
		}
		temp = temp->next;
	}
	return(0);
}


void	do_no_pipe(t_all *all)
{
	if (is_built_in(all) == 0)
	{
		printf("j'exit apres mon built in / PAS DE PIPE \n");
		return;
	}
	else
	{
		ft_putstr_fd("je vais execve/ PAS DE PIPE\n", 2);
		exec_cmd(all);
	}
}

void	open_all_pipe(t_all *all)
{
	int i;
	
	i = 0;
	while(i < all->pipe.nb_pipe)
	{
		if (pipe(all->pipe.pipe_fd[i]) == -1)
		{
			perror("pipe");
			ft_exit("", all, 1);
		}
		i++;
	}
}
void	close_all_fd(t_all *all) // close des pipes
{
	int i;

	i = 0;
	while (i < all->pipe.nb_pipe)
	{
		close(all->pipe.pipe_fd[i][0]);
		close(all->pipe.pipe_fd[i][1]);
		i++;
	}
}

void	do_pipe(t_all *all) //dans process enfant faire exit(1) pas ft_exit 
{ //(lenfant le fait lui meme)
	all->pipe.pid[all->pipe.pipe] = fork();				// ---------FORK ICI
	if (all->pipe.pid[all->pipe.pipe] == -1)
	{
		perror("fork");
		ft_exit("", all, 1);
	}
	if (all->pipe.pid[all->pipe.pipe] == 0)
	{
		ft_putstr_fd("\n----------------------Pipeline ", 2);
		ft_putnbr_fd(all->pipe.pipe, 2);
		ft_putstr_fd(" -----------------------PIPE et je suis dans do pipe\n", 2);

		//if (herdoc_in(pipe))
		if (search_pipe_redir(all->pipe.pipe, REDIRECT_IN, all))//|| search_pipe_redir(all->pipe.pipe, HEREDOC, all)
		{
			ft_putstr_fd("RENTRE ICI PLZ IL Y A REDIRECTION IN\n", 2);
			if (do_redir_fd(all) == -1)
				exit(1);//sauf si built-in dans parent //si un infile foire ou un out alors fail = -1
		}
		else if (all->pipe.pipe != 0)
		{
			ft_putstr_fd("REDIRECTION IN du pipe precedent\n", 2);
			dup2(all->pipe.pipe_fd[all->pipe.pipe - 1][0], STDIN_FILENO);
		}
		// else if (all->pipe.nb_pipe != 0 && all->pipe.pipe > 0) // commande du milieu SANS REDIRECTION
		// {
		// 	ft_putstr_fd("REDIRECTION IN depuis le pipeline ", 2);
		// 	ft_putnbr_fd(all->pipe.pipe, 2);
		// 	ft_putstr_fd(" \n", 2);
		// 	dup2(all->pipe.pipe_fd[all->pipe.pipe - 1][0], STDIN_FILENO);
		// }
		if (search_pipe_redir(all->pipe.pipe, REDIRECT_OUT, all) || 
			search_pipe_redir(all->pipe.pipe, APPEND_OUT, all)) //si au moins une redir alors faire redir
		{
			ft_putstr_fd("RENTRE ICI PLZ IL Y A REDIRECTION OUT\n", 2);
			if (do_redir_fd(all) == -1)
				exit(1);//sauf si built-in dans parent //si un infile foire ou un out alors fail = -1
		}
		else if (all->pipe.pipe < all->pipe.nb_pipe) // derniere commande
		{
			ft_putstr_fd("REDIRECTION OUT dans pipe depuis le pipeline numero ", 2);
			ft_putnbr_fd(all->pipe.pipe, 2);
			ft_putstr_fd(" derniere commande donc pas de dup2\n", 2);
			dup2(all->pipe.pipe_fd[all->pipe.pipe][1], STDOUT_FILENO);
		}
		// else if (all->pipe.pipe != 0) // premiere commande
		// {
		// 	ft_putstr_fd("REDIRECTION OUT dans pipe depuis le pipeline ", 2);
		// 	ft_putnbr_fd(all->pipe.pipe, 2);
		// 	ft_putstr_fd(" pipe milieu \n", 2);
		// 	dup2(all->pipe.pipe_fd[all->pipe.pipe][1], STDOUT_FILENO);
		// }
		close_all_fd(all); // close avant si exit ?
		if (all->pipe.cmd_args[all->pipe.pipe])
		{
			if (is_built_in(all) == 0)
				ft_exit("j'exit apres mon built in la??\n",all, 0);
			else
			{
				ft_putstr_fd("je vais execve\n", 2);
				exec_cmd(all);
			}
		}
		printf("JAI PAS EXECVE\n");
	}
}

// echo nouveau1 >out1 | echo nouveau21 | cat | cat >out2 | echo nouveau31 | cat
//   echo a >out1 | echo b > out2 | >out3 echo c | > out4 echo d | echo e                     TEST IN
//     cat out1
//     cat out2

void	exec_part(t_all *all)
{
	int status;
	all->pipe.pid = gc_malloc(all, sizeof(pid_t) * (all->pipe.nb_pipe + 1)); //sizeof(int *)
	alloc_my_pipe_fd(all);
	//int fail;
	int i;

	i = 0; 
	open_all_pipe(all);
	while(all->pipe.pid && i < all->pipe.nb_pipe + 1) //exec dans enfant
	{
		//ft_putstr_fd("hello ?? \n", 2);
		if (all->pipe.nb_pipe < 1 && is_built_in(all) == 0)
		{
			ft_putstr_fd("je rentre dans no pipe, pipeline =", 2);
			ft_putnbr_fd(all->pipe.pipe, 2);
			ft_putstr_fd(" \n", 2);
			//do_no_pipe(all);

			return;
		}
		else
		{
			ft_putstr_fd("je rentre dans do_pipe, pipeline = ", 2);
			ft_putnbr_fd(all->pipe.pipe, 2);
			ft_putstr_fd(" \n", 2);
			do_pipe(all); //fork la dedans
		}

		i++;
		//printf("i =%d\n", i);
		all->pipe.pipe++;
	}
	close_all_fd(all);
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
	all->pipe.pipe = 0;
	all->pipe.nb_pipe = 0;
}



