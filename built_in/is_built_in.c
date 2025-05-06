#include "minishell.h"

int	is_built_in(t_all *all)
{
	if (!all->pipe.cmd_args || !all->pipe.cmd_args[all->pipe.nb_pipe] || !all->pipe.cmd_args[all->pipe.nb_pipe][0])
	{
		printf("REGIS POURQUOI JAI PAS DARGS\n");
		return(0);
	}
	if (!all->pipe.cmd_args)
    {
        printf("cmd_args is NULL\n");
        return (0);
    }
    if (!all->pipe.cmd_args[all->pipe.nb_pipe])
    {
        printf("cmd_args[%d] is NULL\n", all->pipe.nb_pipe);
        return (0);
    }
    if (!all->pipe.cmd_args[all->pipe.nb_pipe][0])
    {
        printf("cmd_args[%d][0] is NULL\n", all->pipe.nb_pipe);
        return (0);
    }
	if (ft_strncmp(all->pipe.cmd_args[all->pipe.nb_pipe][0], "echo", 4) == 0
		&& all->pipe.cmd_args[all->pipe.nb_pipe][0][4] == '\0')
		return(do_echo(all->pipe.cmd_args, all->pipe.nb_pipe), 1);
	// if (ft_strncmp(all->pipe.cmd_args[all->pipe.nb_pipe][0], "cd", 2) == 0
	// 	&& all->pipe.cmd_args[all->pipe.nb_pipe][0][2] == '\0')
	// 	do_cd(all->pipe.cmd_args, all->pipe.nb_pipe);
	if (ft_strncmp(all->pipe.cmd_args[all->pipe.nb_pipe][0], "env", 3) == 0
		&& all->pipe.cmd_args[all->pipe.nb_pipe][0][3] == '\0')
		return(print_node_env(all->env), printf("BIENSUR QUE JE RETURN1---------------------===========-----------------=========---------"), 1);
	// if (ft_strncmp(all->pipe.cmd_args[all->pipe.nb_pipe][0], "exit", 4) == 0
	// 	&& all->pipe.cmd_args[all->pipe.nb_pipe][0][4] == '\0')
	// 	do_exit(all->pipe.cmd_args, all->pipe.nb_pipe);
	// if (ft_strncmp(all->pipe.cmd_args[all->pipe.nb_pipe][0], "export", 6) == 0
	// 	&& all->pipe.cmd_args[all->pipe.nb_pipe][0][6] == '\0')
	// 	do_export(all->pipe.cmd_args, all->pipe.nb_pipe);
	// if (ft_strncmp(all->pipe.cmd_args[all->pipe.nb_pipe][0], "pwd", 3) == 0
	// 	&& all->pipe.cmd_args[all->pipe.nb_pipe][0][3] == '\0')
	// 	do_pwd(all->pipe.cmd_args, all->pipe.nb_pipe);
	// if (ft_strncmp(all->pipe.cmd_args[all->pipe.nb_pipe][0], "unset", 5) == 0
	// 	&& all->pipe.cmd_args[all->pipe.nb_pipe][0][5] == '\0')
	// 	do_unset(all->pipe.cmd_args, all->pipe.nb_pipe);
	return (0);
}
