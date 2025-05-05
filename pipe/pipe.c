/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdsiurds <mdsiurds@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:38:24 by mdsiurds          #+#    #+#             */
/*   Updated: 2025/05/05 18:06:24 by mdsiurds         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mandatory/minishell.h"

char	*ft_strjoin3(char *s1, char *s2, char *s3, t_all *all)
{
	char	*s4;
	char	*s5;

	s4 = ft_strjoin(s1, s2);
	if (!s4)
		ft_exit("Cannot allocate memory", all, 12);
	s5 = ft_strjoin(s4, s3);
	if (!s5)
		ft_exit("Cannot allocate memory", all, 12);
	free(s4);
	return (s5);
}


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
		free_array(env);
		printf("-----------REGIS TU MAS PAS DONNER DE CMD :O JE FAIS QUOI ?oO---------------------"); // cas possible si pas de cmd donc pas de ft_exit a faire. a enlever plus tard
		return ;
	}
	cmd = all->pipe.cmd_args[pipe];
	if (ft_strchr(all->pipe.cmd_args[pipe][0], '/'))
		all->pipe.cmd_path[pipe] = all->pipe.cmd_args[pipe][0];
	else
	{
		int i = 0;
		while (env && env[i] && ft_strncmp(env[i], "PATH=", 5) != 0)
		i++;
		if (!env[i])
		{
			// ft_putstr_fd(args1, 2);
			// ft_putstr_fd(": command not found\n", 2);   a modifier
			// exit(127);
		}
		path_to_search = ft_split(env[i] + 5, ':');
		if (!path_to_search)
		{
			// exit(1); a modif
		}
		path = search_good_path(path_to_search, all);
	}
	/* path = NULL;
	path = all->pipe.cmd_path[pipe]; */
	
	execve(path, cmd, env);
	
	//pipe++;
	free_array(env);
	//free_array(cmd);
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
		tmp = ft_strjoin3(paths[i], "/", all->pipe.cmd_args[all->pipe.pipe][0], all);
		if (access(tmp, X_OK) == 0)
			return (tmp);
		i++;
	}
	ft_putstr_fd(all->pipe.cmd_args[all->pipe.pipe][0], 2); // ?? 
	ft_putstr_fd(": command not found\n", 2); // ?? 
	// puis continue les pipes suivant ??
	return (NULL);
}