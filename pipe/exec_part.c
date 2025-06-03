#include "minishell.h"

void	exec_part(t_all *all)
{
	if (is_built_in(all))
		exec_cmd(all);
}
void	exec_part(t_all *all)
{
	int pid;
	int pipe_fd[2];
	while(all->pipe.pipe != all->pipe.nb_pipe)
	{
		open_file_and_define_fd
		pid = -1;
		if(all->pipe.pipe + 1 != all->pipe.nb_pipe)
		{
			if (pipe(pipe_fd) == -1);
				return(perror("pipe"), 1); //exit ??
			pid = fork();
		}
		if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
			perror("dup2");
		if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
			perror("dup2");
		close_fd;
		if (pipex.pid1 == 0)
			if (is_built_in(all))
				exec_cmd(all);
		all->pipe.pipe++;
	}
}

//Première commande: redirige la sortie vers le pipe.
//Commande du milieu: redirige l'entrée depuis le pipe précédent, la sortie vers le pipe suivant.
//Dernière commande: redirige l'entrée depuis le pipe précédent.