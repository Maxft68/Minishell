/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdsiurds <mdsiurds@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:38:24 by mdsiurds          #+#    #+#             */
/*   Updated: 2025/04/24 14:30:56 by mdsiurds         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_cmd(t_all *all, char **env)
{
	char **temp = do_char_env(all);
	char **cmd;
	char *path;
	
	cmd[0] = "ls";
	cmd[1] = "-la";
	cmd[2] = NULL;
	
	path = "/bin/ls";
	// int	pipe;
	// pipe = all->pipe.pipe;
	// cmd = all->pipe.cmd_args[pipe];
	// path = all->pipe.cmd_path[pipe];
	execve(path, cmd, temp);
	//pipe++;
	free_array(temp);
}

