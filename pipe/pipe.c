/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdsiurds <mdsiurds@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:38:24 by mdsiurds          #+#    #+#             */
/*   Updated: 2025/04/24 15:59:47 by mdsiurds         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_cmd(t_all *all)
{
	char **env = do_char_env(all);
	char **cmd = NULL;
	cmd = malloc(sizeof(char *) * 2);
	char *path;
	
	cmd[0] = NULL;
	//cmd[1] = "-la";
	cmd[1] = NULL;
	
	path = NULL;
	
	
	// int	pipe;
	// pipe = all->pipe.pipe;
	//cmd = all->pipe.cmd_args[pipe];
	// path = all->pipe.cmd_path[pipe];
	execve(path, cmd, env);
	//pipe++;
	free_array(env);
	free_array(cmd);
}

