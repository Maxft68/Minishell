#include "minishell.h"

void	exec_part(t_all *all)
{
	// if (all->pipe.nb_pipe == 0 && is_built_in(all) == 0) //si 0pipe et built in
	// 	return ;
	// else
	// 	exec_part2(all);
	int old_pipe[2];
	int has_old_pipe = 0; // pour savoir si on a un pipe precedent
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
			if (has_old_pipe)
			{
				dup2(old_pipe[0], STDIN_FILENO);
				close(old_pipe[0]);
				close(old_pipe[1]);
			}
			if (all->pipe.pipe < all->pipe.nb_pipe)
			{
				dup2(all->pipe.pipe_fd[1], STDOUT_FILENO);
				close(all->pipe.pipe_fd[0]);
				close(all->pipe.pipe_fd[1]);
			} 
			
			if (all->pipe.pipe < all->pipe.nb_pipe)// sauvegarder pipe pour le prochain pipe
			{
				old_pipe[0] = all->pipe.pipe_fd[0];
				old_pipe[1] = all->pipe.pipe_fd[1];
				has_old_pipe = 1; // on a un pipe pour le suivant
			}

			close(all->pipe.pipe_fd[0]);
			close(all->pipe.pipe_fd[1]);
			if (is_built_in(all) == 0)
				ft_exit("",all, 0);
			exec_cmd(all);
		}
		if (has_old_pipe)
		{
			close(old_pipe[0]);
			close(old_pipe[1]);
		}
		
		// Sauvegarder le nouveau pipe pour la prochaine itération
		if (all->pipe.pipe < all->pipe.nb_pipe)
		{
			old_pipe[0] = all->pipe.pipe_fd[0];
			old_pipe[1] = all->pipe.pipe_fd[1];
			has_old_pipe = 1;
		}
		all->pipe.pipe++;
	}
	int i = all->pipe.nb_pipe;
	
	waitpid(all->pipe.pid[i - 1], NULL, 0);
	waitpid(all->pipe.pid[i], NULL, 0);
	all->pipe.pipe = 0;
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
// 			perror("dup2");
// 		if (dup2(all->pipe.pipe_fd[1], STDOUT_FILENO) == -1)
// 			perror("dup2");
// 		//close(pipe_fd[1]);
// 		if (pid == 0)
// 			if (is_built_in(all))
// 				exec_cmd(all);
// 		//if old_fd    dup(oldfd, new fd)
// 		all->pipe.pipe++;
// 	}
// }

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