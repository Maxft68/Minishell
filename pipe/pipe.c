

#include "../mandatory/minishell.h"


void	exec_cmd(t_all *all)
{
	char **env = do_char_env(all);
	char **cmd = NULL;
	// cmd = malloc(sizeof(char *) * 3);
	char *path;
	char **path_to_search = NULL;
	int	pipe;
	// cmd[0] = "/bin/ls";
	// cmd[1] = "-la";
	// cmd[2] = NULL;
	
	// path = "/bin/ls";
	pipe = all->pipe.pipe;
	if (!all->pipe.cmd_args || !all->pipe.cmd_args[pipe])
	{
		//free_array(env); dans gc malloc env export
		printf("-----------REGIS TU MAS PAS DONNER DE CMD :O JE FAIS QUOI ?oO---------------------"); // cas possible si pas de cmd donc pas de ft_exit a faire. a enlever plus tard
		return ;
	}
	cmd = all->pipe.cmd_args[pipe];
	if (ft_strchr(all->pipe.cmd_args[pipe][0], '/'))
		path = all->pipe.cmd_args[pipe][0];
	else
	{
		int i = 0;
		while (env && env[i] && ft_strncmp(env[i], "PATH=", 5) != 0)
		i++;
		if (!env[i]) //quand env nexiste plus
		{
			// ft_putstr_fd(args1, 2);
			// ft_putstr_fd(": command not found\n", 2);   a modifier
			// exit(127);
		}
		path_to_search = gc_split(all, env[i] + 5, ':');
		if (!path_to_search)
		{
			// exit(1); a modif
		}
		path = search_good_path(path_to_search, all);
		if (!path)
			return; // et donner le code erreur 127 ? 
	}
	/* path = NULL;
	path = all->pipe.cmd_path[pipe]; */
	
	if (execve(path, cmd, env) == -1)
		printf("-=-=-=-execve fail-=-=--\n");
}
/* 
void	search_good_path(char **paths, t_all *all)
{
	int	i;

	i = 0;
	while (*paths && paths[i])
	{
		all->pipe.cmd_path[all->pipe.pipe] = ft_strjoin3(paths[i], "/", all->pipe.cmd_args[all->pipe.pipe][0], all);
		if (access(all->pipe.cmd_path[all->pipe.pipe], X_OK) == 0)
			return ;
		i++;
	}
	ft_putstr_fd(all->pipe.cmd_args[all->pipe.pipe][0], 2); // ?? 
	ft_putstr_fd(": command not found\n", 2); // ?? 
	// puis continue les pipes suivant ??
} */

char	*search_good_path(char **paths, t_all *all)
{
	int	i;
	char *tmp;

	i = 0;
	while (*paths && paths[i])
	{
		tmp = gc_strjoin3(paths[i], "/", all->pipe.cmd_args[all->pipe.pipe][0], all);
		if (access(tmp, X_OK) == 0)
			return (tmp);
		//free(tmp); // chemin non trouvee donc soit env inexistant soit cmd invalide
		i++;
	}
	ft_putstr_fd(all->pipe.cmd_args[all->pipe.pipe][0], 2); // ?? 
	ft_putstr_fd(": command not found\n", 2); // ??
	//
	// puis continue les pipes suivant ??
	return (NULL);
}