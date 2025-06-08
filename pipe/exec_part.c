// #include "minishell.h"
#include "../mandatory/minishell.h"


void	exec_part(t_all *all)
{
	if (is_built_in(all))
		exec_cmd(all);
}

// void	exec_part(t_all *all)
// {
// 	int pid;
// 	int pipe_fd[2];
// 	all->pipe.pipe = 0; // a verifier si besoin entre deux readlines 
// 	while(all->pipe.pipe != all->pipe.nb_pipe) // si 1 pipe alors se lance 2x
// 	{
// 		//open_file_and_define_fd
// 		pid = -1;
// 		if(all->pipe.pipe + 1 != all->pipe.nb_pipe)
// 		{
// 			if (pipe(pipe_fd) == -1);
// 				return(perror("pipe"), 1); //exit ??
// 			pid = fork();
// 		}
// 		if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
// 			perror("dup2");
// 		if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
// 			perror("dup2");
// 		//close_fd;
// 		if (pid == 0)
// 			if (is_built_in(all))
// 				exec_cmd(all);
// 		all->pipe.pipe++;
// 	}
// }

//Première commande: redirige la sortie vers le pipe.
//Commande du milieu: redirige l'entrée depuis le pipe précédent, la sortie vers le pipe suivant.
//Dernière commande: redirige l'entrée depuis le pipe précédent. 