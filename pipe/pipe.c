

#include "../mandatory/minishell.h"


char	*find_path_cmd(t_all *all, char **env)
{
	char **path_to_search = NULL;
	int i = 0;
	char *path;

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

void	exec_cmd(t_all *all)
{
	char **env = do_char_env(all);
	char **cmd = NULL;
	char *path;
	if (!all->pipe.cmd_args || !all->pipe.cmd_args[all->pipe.pipe])
	{
		printf("-----------REGIS TU MAS PAS DONNER DE CMD :O JE FAIS QUOI ?oO---------------------"); // cas possible si pas de cmd donc pas de ft_exit a faire. a enlever plus tard
		return ;
	}
	cmd = all->pipe.cmd_args[all->pipe.pipe];
	if (ft_strchr(cmd[0], '/'))
		path = all->pipe.cmd_args[all->pipe.pipe][0];
	else
		path = find_path_cmd(all, env);
	
	/* path = NULL;
	path = all->pipe.cmd_path[pipe]; */
	
	if (execve(path, cmd, env) == -1)
		printf("-=-=-=-execve fail-=-=--\n");
}


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