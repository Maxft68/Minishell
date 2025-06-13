#include "../mandatory/minishell.h"

void	exec_part(t_all *all)
{
	// if (all->pipe.nb_pipe == 0 && is_built_in(all) == 0) //si 0pipe et built in
	// 	return ;
	// else
	// 	exec_part2(all);
	int old_pipe[2];
	all->pipe.pipe = 0;
	int has_old_pipe = 0; // pour savoir si on a un pipe precedent

	if (all->pipe.nb_pipe == 0 && is_built_in(all) == 0)
	{
		printf("jexecute un built in et 0 pipe\n");
		return;
	}
	// else if (all->pipe.nb_pipe == 0)
	// {
	// 	if(exec_cmd(all))
	// 		return;
	// }


	while(all->pipe.pipe != all->pipe.nb_pipe + 1)
	{
		if (all->pipe.pipe < all->pipe.nb_pipe)
		{
			if (pipe(all->pipe.pipe_fd) == -1)
			{
				perror("pipe");
				return; //exit ??
			}
		}
		all->pipe.pid[all->pipe.pipe] = fork(); // ---------FORK ICI
		if (all->pipe.pid[all->pipe.pipe] == 0)
		{
			if (search_pipe_redir(all->pipe.pipe, REDIRECT_IN, all))
			{
				all->pipe.fd_infile = open(search_pipe_redir(all->pipe.pipe, REDIRECT_IN, all), O_RDONLY);
				if (all->pipe.fd_infile == -1)
				{
					perror("open infile");
					exit(1);
				}
				printf("JE DEVRAIS PAS DU TOUT ETRE LA OMG\n");
				dup2(all->pipe.fd_infile, STDIN_FILENO);
				close(all->pipe.fd_infile);
			}
			else if (has_old_pipe) // si on a un pipe precedent
			{
				printf("JE DEVRAIS PAS DU TOUT ETRE LA OMG1111\n");
				dup2(old_pipe[0], STDIN_FILENO);
				close(old_pipe[0]);
				close(old_pipe[1]);
			}

			if(search_pipe_redir(all->pipe.pipe, REDIRECT_OUT, all))
			{
				all->pipe.fd_outfile = open(search_pipe_redir(all->pipe.pipe, REDIRECT_OUT, all ), O_WRONLY | O_CREAT | O_TRUNC, 0644);
				if (all->pipe.fd_outfile == -1)
				{
					perror("open outfile");
					exit(1);
				}
				dup2(all->pipe.fd_outfile, STDOUT_FILENO);
				close(all->pipe.fd_outfile);
			}
			else if(all->pipe.pipe < all->pipe.nb_pipe)
			{
				dup2(all->pipe.pipe_fd[1], STDOUT_FILENO);
				close(all->pipe.pipe_fd[0]);
				close(all->pipe.pipe_fd[1]);
			} 
			
			if (all->pipe.pipe < all->pipe.nb_pipe && all->pipe.nb_pipe > 0)// sauvegarder pipe pour le prochain pipe
			{
				if (all->pipe.pipe_fd[0])
				{
					old_pipe[0] = all->pipe.pipe_fd[0];
					printf("numero de pipe= %d, jai un old_pipe[0]\n", all->pipe.pipe);
				}
				if (all->pipe.pipe_fd[1])
				{
					old_pipe[1] = all->pipe.pipe_fd[1];
					printf("numero de pipe= %d, jai un old_pipe[1]\n", all->pipe.pipe);
				}
				if (all->pipe.fd_infile)
				{
					old_pipe[0] = all->pipe.fd_infile;
					printf("numero de pipe= %d, jai un fd_infile\n", all->pipe.pipe);
				}
				if (all->pipe.fd_outfile)
				{
					old_pipe[1] = all->pipe.fd_outfile;
					printf("numero de pipe= %d, jai un fd_outfile ?\n", all->pipe.pipe);
				}
				has_old_pipe = 1; // on a un pipe pour le suivant
			}

			close(all->pipe.pipe_fd[0]);
			close(all->pipe.pipe_fd[1]);
			if (all->pipe.cmd_args[all->pipe.pipe])
			{
				if (is_built_in(all) == 0)
					ft_exit("jexite apres mon built in\n",all, 0);
				printf("je vai execve\n");
				exec_cmd(all);
			}
			printf("JAI PAS EXECVE\n");
			//return; // dans le if ou pas ? 
		}
		if (has_old_pipe && all->pipe.nb_pipe > 0)
		{
			close(old_pipe[0]);
			close(old_pipe[1]);
		}
		
		// Sauvegarder le nouveau pipe pour la prochaine fois
		if (all->pipe.pipe < all->pipe.nb_pipe && all->pipe.nb_pipe > 0)
		{
			old_pipe[0] = all->pipe.pipe_fd[0];
			old_pipe[1] = all->pipe.pipe_fd[1];
			has_old_pipe = 1;
		}
		all->pipe.pipe++;
	}
	int i = 0;

	while (i <= all->pipe.nb_pipe)
	{
		waitpid(all->pipe.pid[i], NULL, 0);
		i++;
	}
	//printf("jarrive laaaaaaaaaaaaaaaaaaaaaa\n");
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