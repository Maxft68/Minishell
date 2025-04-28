/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbier <rbier@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 14:19:33 by mdsiurds          #+#    #+#             */
/*   Updated: 2025/04/27 17:28:42 by rbier            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft/libft.h"
# include "../libft/printf/ft_printf.h"
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
	char ***cmd_args; // [numero de pipe]{"ls", "-l", NULL}
	char **cmd_path; // [numero de pipe]"/bin/ls"
	char ***infile;   // NULL si pas de redirection [pipe][infile][characteres]
	//int					nb_infile;
	char ***outfile; // [numero de pipe]NULL si pas de redirection
	//int					nb_outfile;
	int *pipe_in;    // 1 si doit lire d’un pipe // 0 si doit lire d'un infile ?
	int *pipe_out;   // 1 si doit écrire dans un pipe																							{0, 1, 1, 0, 1, 1} pipe0 = echo >out >>out1 >>out2 >out3 >>out4 >>out5 | >out6 >out7 >>out8 >out21 >>out22 | cat  | >out9
	int **append;     // 1 si ">>" (ajoute a la fin) // 0 si ">" (efface le fichier)  Initialiser à -1	Pour détecter les erreurs facilement	{0, 0, 1, 0, 1} pipe1
	int pipe;        // numero du pipe	 																										{-1} pipe2
	int					nb_pipe;																									//			{0} pipe3
}							t_pipe;

typedef struct s_env
{
	char				*name;
	char				*value;
	struct s_env		*next;
}						t_env;

typedef struct s_lexer
{
    const char  *input;
    int         position;
    char        c;
    bool        first_token;
}       t_lexer;

// typedef enum s_tok_def
// {
// 	WORD,
// 	D_QUOTE,
// 	S_QUOTE,
// 	PIPE,
// 	REDIR_IN,
// 	REDIR_OUT,
// 	REDIR_APPEND,
// 	HERDOC,
// 	CMD
	
// }						t_tok_def;

typedef enum
{
	WTF,
    COMMAND,
    ARG,
    SQ_STRING,
	DQ_STRING,
    PIPE,
    REDIRECT_OUT,
    REDIRECT_IN,
    APPEND_OUT,
    HEREDOC,
    VARIABLE,
    ILLEGAL,
}       token_type;

typedef struct  s_token
{
    token_type      type;
    char            *str;
    // int             index;
    struct s_token  *next;
	// struct s_token	*prev;
}  					t_token;

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
	t_lexer				*lexer;
	t_token				*token;
	t_garbage			*garbage;
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
void		exec_cmd(t_all *all, char **env);
/* ********Fonctions lexing parsing************ */
void		create_lexer(const char *input, t_all *all);
void		create_token(token_type type, const char *str, t_all *all);
void		advance_char(t_lexer *lexr);
void		next_token(t_all *all);
void		skip_whitespace(t_lexer *lexr);
int			new_tkn_char(char c);
void		create_word_token(t_all *all);
void 		create_string_token(char quote, t_all *all);
void		create_operator_token(token_type type, const char *str, t_all *all);
void		ft_tknadd_back(t_token **lst, t_token *tkn);
t_token		*ft_tknlast(t_token *lst);
void		print_node(t_token *token);//-------------------------debug
void    	list_to_tab(t_all *all);
char		*gc_strdup(const char *s, t_all *all);


#endif
