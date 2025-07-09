#include "../mandatory/minishell.h"

volatile sig_atomic_t g_sigint_flag = 0;


// int	main(int argc, char **argv, char **env)
// {
// 	char	*read_copy;
// 	char	*read;
// 	t_all	all;

// 	if (argc != 1)
// 		return (1); 
// 	ft_memset(&all, 0, sizeof(t_all));
// 	do_env(&all, env);	
// 	//signal(SIGQUIT, SIG_IGN);
// 	//signal(SIGQUIT, SIG_DFL); // a remettre dans chaque enfant 
// 	//signal(SIGINT, SIG_IGN);
// 	while (1)
// 	{
// 		read_copy = readline("WriteOnMe ");
// 		if (!read_copy)
// 			ft_exit("exit avec ctrl + D\n", &all, 0);
// 		read = gc_strdup(read_copy, &all);
// 		free(read_copy);
// 		if (ft_strncmp(read, "aaa", 3) == 0)// a remplacer par le signal CTRL + C
// 		{					// a remplacer par le signal CTRL + C
// 			ft_exit("FINISH\n", &all, 0);// a remplacer par le signal CTRL + C
// 		}									// a remplacer par le signal CTRL + C
// 		if (read && read[0] != '\0')
// 			add_history(read);
// 		else						//Quand il ny a que des espaces dans read ??
// 			continue;
// 		create_lexer(read, &all);
// 		while (all.lexer->c)
// 			next_token(&all);
// 		print_node(all.token);
// 		list_to_tab(&all);
// 		exec_part(&all);
// 		ft_lstclear(&all.token); // a rajouter dans ft_exit ?
// 		free_garbage_collect(&all.garbage);
// 	}
// 	(void)argv;
// } 

int	main(int argc, char **argv, char **env)
{
	t_all all;

	if (argc != 1)
		return (printf("Just one arg, or nothing\n"), 1);
	//printf("--------nouveau minishell----------\n");
	ft_memset(&all, 0, sizeof(t_all));
	do_env(&all, env);
	signal(SIGQUIT, SIG_IGN);
	//signal(SIGQUIT, SIG_DFL); // a remettre dans chaque enfant 
	while (1)
	{
		// 
		signals_swing();
		char *firstinput = readline("WriteOnMe ");
		if (!firstinput)
			break;
		char *input = gc_strdup_input(firstinput, &all);
		if (create_lexer(input, &all) != -1)
			if (pars_to_exec(&all) != 0)
				ft_putstr_fd("Error in execution\n", 2);
		//testerprintf("sig_atomic:%d\n", g_sigint_flag);
		// ft_lstclear(&all.token);
		// ft_lstclear(&all.rdir_tkn);
		free_garbage_collect(&all.garbage);
		all.garbage = NULL;
		all.token = NULL;
		all.rdir_tkn = NULL;
	}
	// printf("d_quote= %s\n", all.lexer->d_quote ? "true" : "false");
	// printf("s_quote= %s\n", all.lexer->s_quote ? "true" : "false");
	//testerft_exit("exit final apres boucle while\n", &all, all.error_code); // ?? utile dans un monde parallele ?
	(void)argv;
}
