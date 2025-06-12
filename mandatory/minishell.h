

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
# include <stddef.h>
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
	void				*pointer;
	struct s_garbage	*next;
}						t_garbage;

typedef struct s_garbage_env
{
	void				*pointer;
	struct s_garbage_env	*next;
}						t_garb_env;


typedef struct s_pipe
{
	char					***cmd_args; // [numero de pipe]{"ls", "-l", NULL}
	char					**cmd_path; // [numero de pipe]"/bin/ls"
	int						pipe;        // numero du pipe actuel
	int						nb_pipe; //nombre de pipe total
	int						pipe_fd[2]; // [0] lecture  [1] ecriture
	int						fd_infile;
	int						fd_outfile;
	
}							t_pipe;

typedef struct s_env
{
	char				*name;
	//int					equal; pour savoir si afficher le = ou non ?
	char				*value;
	struct s_env		*next;
}						t_env;

typedef struct s_export
{
	char				*name;
	//int					equal; pour savoir si afficher le = ou non ?
	char				*value;
	struct s_export		*next;
}						t_export;

typedef struct s_lexer
{
    const char  *input;
    int         position;
    char        c;
	bool		s_quote;
	bool		d_quote;
    bool        cmd;
	bool		redir;
}       t_lexer;

typedef enum token_type
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
	REDIR_FILE,
    VARIABLE,
    ILLEGAL,
}       token_type;

typedef struct  s_token
{
    token_type      type;
    char            *str;
    int             pipe;
    struct s_token  *next;
	// struct s_token	*prev;
}  					t_token;


typedef struct s_data // structure poubelle pour stocker un peu de tout
{
	int			len_name;
	int			len_value;
	char		*name;
	char		*value;
	int			code_exit;
	int			egal;
	char		*val;
	char		*n;
	int			add;
	char		*pwd;
	char		*oldpwd;
	int			j;
	int			t;
	int			x;
	int			z;
	char		*new;
	char		*tmp;
	char		*temp;

}						t_data;



typedef struct	s_env_export
{
	int					nb_line_env; // donc +1 pour malloc
	int					nb_line_export;
}				t_env_export;

typedef struct s_all
{
	t_pipe				pipe;
	t_env				*env;
	t_lexer				*lexer;
	t_token				*token;
	t_token				*rdir_tkn;
	t_garbage			*garbage;
	t_garb_env			*garbage_env;
	t_data				data;
	t_env_export		env_export;
	t_export			*export;
	int					error_code;     // pour le code exit status
}						t_all;

void		ft_exit(char *error, t_all *all, int error_code);
void		do_node(char **read_array, t_all *all);
void		ft_lstadd_front(t_garbage **garbage, t_garbage *new);
void		ft_lstadd_front_gc_env(t_garb_env **garbage_env, t_garb_env *new);
void		ft_lstclear(t_token **token);
void		free_array(char **array);
t_env		*ft_lstnew_env(t_all *all, char *name, char *value);
t_garb_env	*ft_lstnew(t_all *all, void *alloc);
void		ft_lstadd_back_env(t_env **env, t_env *new);
int			ft_strcmp(char *s1, char *s2);
/* **********Garbage************************************************** */
void		*gc_malloc(t_all *all, size_t size);
void		*gc_malloc_env(t_all *all, size_t size);
char		**gc_split(t_all *all, char *s, char c);
char		*gc_strjoin(t_all *all, char *s1, char *s2);
char		*gc_strjoin3(char *s1, char *s2, char *s3, t_all *all);
void		free_garbage_collect(t_garbage **garbage);
void		free_garbage_env(t_garb_env **garbage_env_head);
char		*gc_strdup(char *s, t_all *all);
char		*gc_strdup_env(char *s, t_all *all);
char		*gc_strjoin_env(t_all *all, char *s1, char *s2);
char		*gc_substr_env(char *s, unsigned int start, size_t len, t_all *all);
void		ft_lstadd_front_gc_env(t_garb_env **garbage_env, t_garb_env *new);
// char		*gc_realloc(t_all *all, char *old, int big);
void		*gc_realloc(t_all *all, void *ptr, size_t size);
/* **********Lexing parsing************************************************** */
int			create_lexer(char *input, t_all *all);
void    	pars_to_exec(t_all *all);
char		*pick_char(char *str, token_type type, t_all *all);
void		create_token(token_type type, char *str, t_all *all);
void		advance_char(t_lexer *lexr);
void		skip_whitespace(t_lexer *lexr);
int			new_tkn_char(token_type type, t_all *all);
void		ft_tknadd_back(t_token **lst, t_token *tkn);
t_token		*ft_tknlast(t_token *lst);
int 		check_tkn_lst(t_all *all);
void    	create_redir_lst(t_all *all);
char    	*search_pipe_redir(int pipe, token_type type, t_all *all);
void		print_node(t_token *token);//-------------------------debug
void    	list_to_tab(t_all *all);
void		initialize_data(t_all *all, char *old);
void		handle_expand(char *old, t_all *all);
char		*search_pipe_redir(int pipe, token_type type, t_all *all);
/* **********Exec functions************************************************** */
void		exec_cmd(t_all *all);
char		*search_good_path(char **paths, t_all *all);
char		**do_char_env(t_all *all);
void		exec_part(t_all *all);
/* **********Signal functions************************************************ */
void    	signals_swing(void);
/* **********Built_in functions********************************************** */
int			is_built_in(t_all *all);
void		do_echo(char ***args, int pipe);
void		do_env(t_all *all, char **env);
void		print_node_env(t_env *env);
void		free_env(t_env **env);
void		do_export(t_all *all);
void		do_add_env_next(t_all *all, char *s);
void		do_add_env(t_all *all);
void		print_export(t_export *export);
void		ft_lstadd_back_export(t_export **export, t_export *new);
void		copy_list(t_all *all);
void		sort_list(t_all *all);
int			search_env(t_all *all, char *name);
int			replace_env(t_all *all, char *name, char *value);
void		replace_or_add_env(t_all *all, char *name, char *value);
int			is_alpha_str(char *str);
void		sort_list(t_all *all);
void		add_value_env(t_all *all, char *s);
void		print_and_null(t_all *all, char *s);
void		do_unset(t_all *all);
void		do_pwd(t_all *all);
void		do_cd(t_all *all);
char		*find_the_value(t_all *all, char *name);
char		*ft_pwd(t_all *all);

#endif /* MINISHELL_H */
