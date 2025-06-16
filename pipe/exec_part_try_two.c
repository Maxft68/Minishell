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
}

int	do_redir_fd(t_all *all)
{
	t_token *temp;

	temp = all->rdir_tkn;
	while(temp)
	{
		if (temp->type >= 6 && temp->type <= 9)
		{

			if (temp->type == REDIRECT_IN) 
			{
				all->pipe.fd_infile = open(temp->str, O_RDONLY);
				if (all->pipe.fd_infile == -1)
				{
					perror("open infile"); //a verifier si \n ou pas
					ft_exit("", all, 1);//sauf si built-in dans parent
				}
				if (dup2(all->pipe.fd_infile, STDIN_FILENO) == -1)
				{
					perror("dup2 fd_infile");
					ft_exit("", all, 1);//sauf si built-in dans parent
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
				if (temp->type == REDIRECT_OUT)
					all->pipe.fd_outfile = open(temp->str, O_WRONLY | O_CREAT | O_TRUNC, 0644); // a checker le 0644
				if (temp->type == APPEND_OUT)
					all->pipe.fd_outfile = open(temp->str, O_WRONLY | O_CREAT | O_APPEND, 0644); // a checker le 0644
				if (all->pipe.fd_outfile == -1)
					{
						perror("open outfile"); //temp->str ??
						ft_exit("", all, 1);//sauf si built-in dans parent
					}
				if (dup2(all->pipe.fd_outfile, STDOUT_FILENO) == -1)
				{
					perror("dup2 fd_outfile");
					ft_exit("", all, 1);//sauf si built-in dans parent
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
		printf("jexite apres mon built in/ PAS DE PIPE\n");
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

void	do_pipe(t_all *all)
{
	//printf("%d\n", all->pipe.pipe);
	all->pipe.pid[all->pipe.pipe] = fork();				// ---------FORK ICI
	if (all->pipe.pid[all->pipe.pipe] == 0)
	{
		if (all->pipe.pipe == 0 && all->pipe.nb_pipe != 0) // premiere commande
			dup2(all->pipe.pipe_fd[0][1], STDOUT_FILENO);
		else if (all->pipe.pipe == all->pipe.nb_pipe && all->pipe.nb_pipe != 0) // derniere commande
			dup2(all->pipe.pipe_fd[all->pipe.pipe - 1][0], STDIN_FILENO);
		else if (all->pipe.nb_pipe != 0) // commande du milieu
		{
			dup2(all->pipe.pipe_fd[all->pipe.pipe - 1][0], STDIN_FILENO);
			dup2(all->pipe.pipe_fd[all->pipe.pipe][1], STDOUT_FILENO);
		}
		if (search_pipe_redir(all->pipe.pipe, REDIRECT_IN, all) || 
		search_pipe_redir(all->pipe.pipe, REDIRECT_OUT, all) || 
		search_pipe_redir(all->pipe.pipe, HEREDOC, all) || 
		search_pipe_redir(all->pipe.pipe, APPEND_OUT, all)) //si au moins une redir alors faire redir
		if (do_redir_fd(all) == -1)
				ft_exit("", all, 1);//sauf si built-in dans parent //si un infile foire ou un out alors fail = -1
		close_all_fd(all); // close avant si exit ? 
		if (all->pipe.cmd_args[all->pipe.pipe])
		{
			if (is_built_in(all) == 0)
				ft_exit("jexite apres mon built in\n",all, 0);
			else
			{
				ft_putstr_fd("je vais execve\n", 2);
				exec_cmd(all);
			}
		}
		printf("JAI PAS EXECVE\n");
	}
	// else
	// 	waitpid(all->pipe.pid[all->pipe.pipe], NULL, 0);
}

void	exec_part(t_all *all)
{
	all->pipe.pid = gc_malloc(all, sizeof(pid_t) * (all->pipe.nb_pipe + 2)); //sizeof(int *)
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
			return;
		}
		else
			do_pipe(all); //fork la dedans

		i++;
		all->pipe.pipe++;
	}
	close_all_fd(all); //a verifier si fermer les fd dan le parent 
	i = 0;
	all->pipe.pipe = 0;
	while (all->pipe.pid && i < all->pipe.nb_pipe + 1)
	{
		if (waitpid(all->pipe.pid[i], NULL, 0) == -1) //&status pour le code erreur a rajouter plus tard
			ft_exit("WAITPID", all, 1);
		if (i == all->pipe.nb_pipe - 1)
			//signaux(status ...)
		else
			//signaux(status.....)
		i++;
	}
	all->pipe.pipe = 0;
	all->pipe.nb_pipe = 0;
}

// waitpid(pipex.pid1, NULL, 0);
// 	waitpid(pipex.pid2, &status, 0);
// 	if (WIFEXITED(status))
// 		return (WEXITSTATUS(status));

// void	open_and_define_fd(t_all *all)// define fd[0] et fd[1]
// {
// 	if (redir_in(all->pipe.pipe))
// 	{
// 		all->pipe.fd_infile = open(search_pipe_redir(all->pipe.pipe), O_RDONLY);
// 		dup2(all->pipe.fd_infile, STDIN_FILENO);
// 	}
// 	else
// 		if (all->pipe.pipe_fd[1])
// 			all->pipe.fd_infile = all->pipe.pipe_fd[1];
// }

// void	exec_part2(t_all *all)
// {
// 	int pid[all->pipe.nb_pipe + 1];
// 	all->pipe.pipe_fd[2];
// 	all->pipe.pipe = 0; // a verifier si besoin entre deux readlines 
// 	while(all->pipe.pipe != all->pipe.nb_pipe) // si 1 pipe alors se lance 2x
// 	{
// 		pid[all->pipe.pipe] = -1;

// 		if (pipe(all->pipe.pipe_fd) == -1);
// 			return(perror("pipe"), 1); //exit ??
// 		pid[all->pipe.pipe] = fork();

// 		open_and_and_define_fd(all); // define fd[0] et fd[1]
// 		if (dup2(all->pipe.pipe_fd[0], STDIN_FILENO) == -1)
// 		pid[all->pipe.pipe] = -1;

// 		if (pipe(all->pipe.pipe_fd) == -1);
// 			return(perror("pipe"), 1); //exit ??
// 		pid[all->pipe.pipe] = fork();

// 		open_and_and_define_fd(all); // define fd[0] et fd[1]
// 		if (dup2(all->pipe.pipe_fd[0], STDIN_FILENO) == -1)
// 			perror("dup2");
// 		if (dup2(all->pipe.pipe_fd[1], STDOUT_FILENO) == -1)
// 		if (dup2(all->pipe.pipe_fd[1], STDOUT_FILENO) == -1)
// 			perror("dup2");
// 		//close(pipe_fd[1]);
// 		//close(pipe_fd[1]);
// 		if (pid == 0)
// 			if (is_built_in(all))
// 				exec_cmd(all);
// 		//if old_fd    dup(oldfd, new fd)
// 		//if old_fd    dup(oldfd, new fd)
// 		all->pipe.pipe++;
// 	}
// }

//gerer redirection pipe

//gerer redirection pipe

//Première commande: redirige la sortie vers le pipe.
//Commande du milieu: redirige l'entrée depuis le pipe précédent, la sortie vers le pipe suivant.
//Dernière commande: redirige l'entrée depuis le pipe précédent. 

// sans pipe on lance chaque commande dans un enfant
// 	pour ne pas execve dans le parent
// if !is_built_in alors fork



// void	open_file_in(char *name, t_pipex *pipex)
// {
// 	if (pipex->infile && access(pipex->infile, F_OK | R_OK) == -1)
// 	{
// 		perror(pipex->infile);
// 		close_fd(pipex);
// 		exit(127);
// 	}
// 	pipex->infile_fd = open(name, O_RDONLY);
// 	if (pipex->infile_fd == -1)
// 	{
// 		perror(name);
// 		close_fd(pipex);
// 		exit(1);
// 	}
// }

// void	open_file_out(char *name, t_pipex *pipex)
// {
// 	pipex->outfile_fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 	if (pipex->outfile_fd == -1)
// 	{
// 		perror(name);
// 		close_fd(pipex);
// 		exit(1);
// 	}
// }
//echo coucou | cat