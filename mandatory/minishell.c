#include "../mandatory/minishell.h"

volatile sig_atomic_t g_sigint_flag = 0;

int	main(int argc, char **argv, char **env)
{
	t_all all;

	if (argc != 1)
		return (printf("Just one arg, or nothing\n"), 1);
	ft_memset(&all, 0, sizeof(t_all));
	do_env(&all, env);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		// 
		signals_swing();
		// char *firstinput = readline("WriteOnMe "); //a remettre apres mpanic tester
		// if (!firstinput)
		// 	break;
		char *firstinput = readline("minishell $");
		if (!firstinput)
		{
			if (isatty(STDIN_FILENO))
			write(2, "exit\n", 6);
			exit (all.error_code);
		}
		char *input = gc_strdup_input(firstinput, &all);
		if (create_lexer(input, &all) != -1)
			if (pars_to_exec(&all) != 0)
		free_garbage_collect(&all.garbage);
		all.garbage = NULL;
		all.token = NULL;
		all.rdir_tkn = NULL;
	}
	ft_exit("exit\n", &all, all.error_code);
	(void)argv;
}

