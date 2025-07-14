

#include "../mandatory/minishell.h"

char	*find_path_cmd(t_all *all, char **env)
{
	char	**path_to_search;
	int		i;
	char	*path;

	path_to_search = NULL;
	i = 0;
	while (env && env[i] && ft_strncmp(env[i], "PATH=", 5) != 0)
		i++;
	if (!env[i])
		return (ft_putstr_fd("WriteOnMe: ", 2), all->error_code = 127,
			ft_putstr_fd(all->pipe.cmd_args[all->pipe.pipe][0], 2),
			ft_putstr_fd(": No such file or directory\n", 2), NULL);
	path_to_search = gc_split(all, env[i] + 5, ':');
	path = search_good_path(path_to_search, all);
	if (!path)
	{
		ft_putstr_fd(all->pipe.cmd_args[all->pipe.pipe][0], 2);
		ft_putstr_fd(": command not found\n", 2);
		ft_exit("", all, 127);
		return (NULL);
	}
	return (path);
}

int	exec_cmd(t_all *all)
{
	char	**env;
	char	**cmd;
	char	*path;

	env = do_char_env(all);
	cmd = NULL;
	if (!all->pipe.cmd_args || !all->pipe.cmd_args[all->pipe.pipe]
		|| !all->pipe.cmd_args[all->pipe.pipe][0])
		ft_exit("", all, 0);
	cmd = all->pipe.cmd_args[all->pipe.pipe];
	if (cmd && cmd[0] && ft_strchr(cmd[0], '/'))
		path = cmd[0];
	else
		path = find_path_cmd(all, env);
	if (!path)
		return (ft_exit("", all, 127), 1);
	execve(path, cmd, env);
	ft_putstr_fd("WriteOnMe: ", 2);
	perror(cmd[0]);
	ft_exit("", all, 127);
	return (1);
}

char	*search_good_path(char **paths, t_all *all)
{
	int		i;
	char	*tmp;

	tmp = NULL;
	i = 0;
	while (*paths && paths[i])
	{
		if (all->pipe.cmd_args && all->pipe.cmd_args[all->pipe.pipe][0])
			tmp = gc_strjoin3(paths[i], "/",
					all->pipe.cmd_args[all->pipe.pipe][0], all);
		if (tmp)
		{
			if (access(tmp, X_OK) == 0)
				return (tmp);
		}
		i++;
	}
	return (NULL);
}
