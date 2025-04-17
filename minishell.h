/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdsiurds <mdsiurds@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 14:19:33 by mdsiurds          #+#    #+#             */
/*   Updated: 2025/04/17 10:42:36 by mdsiurds         ###   ########.fr       */
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

typedef struct s_garbage
{
	char				*pointer;
	struct s_garbage	*next;
}						t_garbage;

typedef struct s_pipe
{
	char				*infile;   // a  revoir entierement
	int					infile_fd;  // a  revoir entierement
	char				*outfile;  // a  revoir entierement
	int					outfile_fd; // a  revoir entierement
	char				**cmd1_args;
	char				**cmd2_args;
	char				*cmd1_path;
	char				*cmd2_path;
	int					pipe_fd[2];
	int					pid1;
	int					pid2;
}						t_pipe;

typedef struct s_env
{
	char				*name;
	char				*value;
	struct s_env		*next;
}						t_env;

typedef enum s_tok_def
{
	WORD,
	D_QUOTE,
	S_QUOTE,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	HERDOC,
	CMD
	
}						t_tok_def;

typedef struct s_token //
{
	char				*name;
	struct s_token		*next;
}						t_token;

typedef struct s_data // structure poubelle pour stocker un peu de tout
{
	int		len_name;
	int		len_value;
	char	*name;
	char	*value;
}				t_data;

typedef struct s_all
{
	t_pipe				pipe;
	t_env				*env;
	t_token				*token;
	t_garbage			*garbage;
	t_tok_def			tok_def;
	t_data				data;
}						t_all;

void		ft_exit(char *error, t_all *all, int error_code);
void		do_node(char **read_array, t_all *all);
void		ft_lstadd_front(t_garbage **garbage, t_garbage *new);
void		ft_lstclear(t_token **token);
void		free_array(char **array);
void		*gc_malloc(t_all *all, size_t size);
void		free_garbage_collect(t_garbage **garbage);
void		do_env(t_all *all, char **env);
void		print_node_env(t_env *env);
void		free_env(t_env **env);
t_env		*ft_lstnew_env(t_all *all, char *name, char *value);
void		ft_lstadd_back_env(t_env **env, t_env *new);

#endif
