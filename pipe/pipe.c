

#include "../mandatory/minishell.h"


char	*find_path_cmd(t_all *all, char **env)
{
	char **path_to_search = NULL;
	int i = 0;
	char *path;

	while (env && env[i] && ft_strncmp(env[i], "PATH=", 5) != 0)
		i++;
	if (!env[i])
		return(ft_putstr_fd("WriteOnMe: ", 2), all->error_code = 127,
		ft_putstr_fd(all->pipe.cmd_args[all->pipe.pipe][0], 2), 
		ft_putstr_fd(": No such file or directory\n", 2), NULL);
	path_to_search = gc_split(all, env[i] + 5, ':');
	path = search_good_path(path_to_search, all);
	if (!path)
	{
		ft_putstr_fd(all->pipe.cmd_args[all->pipe.pipe][0], 2);
		ft_putstr_fd(": command not found\n", 2);
		return (NULL);
	}
	return(path);
}

int	exec_cmd(t_all *all) // DANS ENFANT
{
	char **env = do_char_env(all);
	char **cmd = NULL;
	char *path;

	if (!all->pipe.cmd_args || !all->pipe.cmd_args[all->pipe.pipe] || !all->pipe.cmd_args[all->pipe.pipe][0])
	{
		//testerprintf("-----------REGIS TU MAS PAS DONNER DE CMD :O JE FAIS QUOI ?oO---------------------"); // cas possible si pas de cmd donc pas de ft_exit a faire. a enlever plus tard
		ft_exit("jfais quoi", all, 0);
	}
	cmd = all->pipe.cmd_args[all->pipe.pipe];
	if (cmd && cmd[0] && ft_strchr(cmd[0], '/'))
		path = cmd[0];
	else
		path = find_path_cmd(all, env);
	if (!path)
		return(ft_exit("",all, 127), 1);
	execve(path, cmd, env); //return si echoue ??
	ft_putstr_fd("WriteOnMe: ", 2);
	perror(cmd[0]);
	printf("-=-=-=-execve fail-=-=--\n");
	ft_exit("", all, 127);
	return(1);
}


char	*search_good_path(char **paths, t_all *all)
{
	int	i;
	char *tmp;
	
	tmp = NULL;
	i = 0;
	while (*paths && paths[i])
	{
		if (all->pipe.cmd_args && all->pipe.cmd_args[all->pipe.pipe][0])
		tmp = gc_strjoin3(paths[i], "/", all->pipe.cmd_args[all->pipe.pipe][0], all);
		if (tmp)
		{
			if (access(tmp, X_OK) == 0)
			return (tmp);
		}
		i++;
	}
	// ft_putstr_fd(all->pipe.cmd_args[all->pipe.pipe][0], 2); // ?? 
	// ft_putstr_fd(": command not found\n", 2); // ??
	return (NULL);
}

// char	*find_path_cmd(t_all *all, char **env)
// {
// 	char **env = do_char_env(all);
// 	char **cmd = NULL;
// 	// cmd = malloc(sizeof(char *) * 3);
// 	char *path;
// 	char **path_to_search = NULL;
// 	int	pipe;
// 	// cmd[0] = "/bin/ls";
// 	// cmd[1] = "-la";
// 	// cmd[2] = NULL;
	
// 	// path = "/bin/ls";
// 	pipe = all->pipe.pipe;
// 	if (!all->pipe.cmd_args || !all->pipe.cmd_args[pipe] || !all->pipe.cmd_args[all->pipe.pipe][0])
// 	{
// 		printf("-----------REGIS TU MAS PAS DONNER DE CMD :O JE FAIS QUOI ?oO---------------------\n"); // cas possible si pas de cmd donc pas de ft_exit a faire. a enlever plus tard
// 		return ;
// 	}
// 	cmd = all->pipe.cmd_args[pipe];
// 	if (ft_strchr(all->pipe.cmd_args[pipe][0], '/'))
// 		path = all->pipe.cmd_args[pipe][0];
// 	else
// 	{
// 		int i = 0;
// 		while (env && env[i] && ft_strncmp(env[i], "PATH=", 5) != 0)
// 		i++;
// 	if (!env[i]) //quand env nexiste plus
// 	{
// 		// ft_putstr_fd(args1, 2);
// 		// ft_putstr_fd(": command not found\n", 2);   a modifier
// 		// exit(127);
// 	}
// 	path_to_search = gc_split(all, env[i] + 5, ':');
// 	if (!path_to_search)
// 	{
// 		// exit(1); a modif
// 	}
// 	path = search_good_path(path_to_search, all);
// 	if (!path)
// 		return (NULL); // et donner le code erreur 127 ?
// 	return (path);
// } 