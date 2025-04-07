/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdsiurds <mdsiurds@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 14:19:33 by mdsiurds          #+#    #+#             */
/*   Updated: 2025/04/07 17:55:31 by mdsiurds         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft/libft.h"
# include "./libft/printf/ft_printf.h"
# include <curses.h>
# include <dirent.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

typedef struct s_pipe
{
	char			*infile; // a  revoir entierement
	int				infile_fd;
	char			*outfile;
	int				outfile_fd;
	char			**cmd1_args;
	char			**cmd2_args;
	char			*cmd1_path;
	char			*cmd2_path;
	int				pipe_fd[2];
	int				pid1;
	int				pid2;
}					t_pipe;

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_token
{
	char			*name;
	struct s_token	*next;
}					t_token;

typedef struct s_all
{
	t_pipe			*pipe;
	t_env			*env;
	t_token			*token;
}					t_all;

void	ft_exit(char *error, t_all *all, int error_code);
void	do_node(char **read_array, t_all *all);
void	ft_lstclear(t_token **token);
void	free_array(char **array);

#endif
