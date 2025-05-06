
#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	char	*read;
	t_all	all;

	if (argc != 1)
		return (1); 
	ft_memset(&all, 0, sizeof(t_all));
	do_env(&all, env);	
	//signal(SIGQUIT, SIG_IGN);
	//signal(SIGQUIT, SIG_DFL); // a remettre dans chaque enfant 
	//signal(SIGINT, SIG_IGN);
	while (1)
	{
		read = readline("WriteOnMe ");
		if (!read)
			ft_exit("exit avec ctrl + D\n", &all, 0);
		if (ft_strncmp(read, "aaa", 3) == 0)// a remplacer par le signal CTRL + C
		{	
			// free(read);							// a remplacer par le signal CTRL + C
			ft_exit("FINISH\n", &all, 0);// a remplacer par le signal CTRL + C
		}									// a remplacer par le signal CTRL + C
		if (ft_strncmp(read, "env", 3) == 0)
		{
			print_node_env(all.env);
		}
		if (read && read[0] != '\0')
			add_history(read);
		else						//Quand il ny a que des espaces dans read
			continue;
		create_lexer(read, &all);
		while (all.lexer->c)
			next_token(&all);
		//printf("coucou\n");
		print_node(all.token);
		//printf("not coucou\n");
		list_to_tab(&all);
		free(read);
		if (!is_built_in(&all))
			exec_cmd(&all); 
		ft_lstclear(&all.token); // a rajouter dans ft_exit ?
		free_garbage_collect(&all.garbage);
		// do_everything
		//exec_cmd(&all);
	}
	// do_char_env(&all);
	// print_char_env(&all);
	(void)argv;
}

