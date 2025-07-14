#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft/libft.h"
# include "../libft/printf/ft_printf.h"
# include <curses.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
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

extern volatile sig_atomic_t	g_sigint_flag;

typedef struct s_garbage
{
	void						*pointer;
	struct s_garbage			*next;
}								t_garbage;

typedef struct s_garbage_env
{
	void						*pointer;
	struct s_garbage_env		*next;
}								t_garb_env;

typedef struct s_pipe
{
	char						***cmd_args;
	char						**cmd_path;
	int							pipe;
	int							nb_pipe;
	int							**pipe_fd;
	int							*pid;
	int							fd_infile;
	int							fd_outfile;
	int							**heredoc_fd;
	int							i;

}								t_pipe;

typedef struct s_env
{
	char						*name;
	char						*value;
	struct s_env				*next;
}								t_env;

typedef struct s_export
{
	char						*name;
	char						*value;
	struct s_export				*next;
}								t_export;

typedef struct s_lexer
{
	const char					*input;
	int							position;
	char						c;
	bool						cmd;
	int							redir;
}								t_lexer;

typedef enum s_token_type
{
	WTF = 0,
	REDIR_FILE = 1,
	HD_EOF = 2,
	COMMAND = 3,
	ARG = 4,
	SQ_STRING = 5,
	DQ_STRING = 6,
	PIPE = 7,
	REDIRECT_OUT = 8,
	REDIRECT_IN = 9,
	APPEND_OUT = 10,
	HEREDOC = 11,
	ILLEGAL = 12,
}								t_token_type;

//

typedef struct s_token
{
	t_token_type				type;
	char						*str;
	int							pipe;
	struct s_token				*next;
}								t_token;

typedef struct s_built_in
{
	int							i;
	int							j;
	int							n;
}								t_built_in;

typedef struct s_exec
{
	int							i;
	int							j;
}								t_exec;

typedef struct s_data
{
	int							len_name;
	int							len_value;
	char						*name;
	char						*value;
	int							code_exit;
	int							egal;
	char						*val;
	char						*n;
	int							add;
	char						*pwd;
	char						*oldpwd;
	int							t;
	int							x;
	int							z;
	char						*new;
	char						*tmp;
	char						*temp;
	bool						s_quote;
	bool						d_quote;
}								t_data;

typedef struct s_hd_data
{
	int							i;
	int							j;
	char						*tmp;
	char						*tmp2;
	char						*new;
	size_t						hd_eof_len;
	size_t						str_len;
}								t_hd_data;

typedef struct s_exit
{
	int							i;
	int							start;
	int							end;
	int							negative;
	int							sign;
}								t_exit;

typedef struct s_env_export
{
	int							nb_line_env;
	int							nb_line_export;
}								t_env_export;

typedef struct s_all
{
	t_built_in					built_in;
	t_pipe						pipe;
	t_env						*env;
	t_lexer						*lexer;
	t_token						*token;
	t_token						*rdir_tkn;
	t_garbage					*garbage;
	t_garb_env					*garbage_env;
	t_data						data;
	t_hd_data					hd_data;
	t_env_export				env_export;
	t_export					*export;
	t_exec						exec;
	int							error_code;
	t_exit						exit;
}								t_all;

void							ft_exit(char *error, t_all *all,
									int error_code);
void							close_all_pipe_exit(t_all *all);
int								ft_close(t_all *all, int *fd);
void							do_node(char **read_array, t_all *all);
void							ft_lstadd_front(t_garbage **garbage,
									t_garbage *new);
void							ft_lstadd_front_gc_env(t_garb_env **garbage_env,
									t_garb_env *new);
void							ft_lstclear(t_token **token);
void							free_array(char **array);
t_env							*ft_lstnew_env(t_all *all, char *name,
									char *value);
t_garb_env						*ft_lstnew(t_all *all, void *alloc);
void							ft_lstadd_back_env(t_all *all, t_env **env,
									t_env *new);
int								ft_strcmp(char *s1, char *s2);
/* **********Garbage************************************************** */
void							*gc_malloc(t_all *all, size_t size);
void							*gc_malloc_env(t_all *all, size_t size);
char							**gc_split(t_all *all, char *s, char c);
char							*gc_strjoin(t_all *all, char *s1, char *s2);
char							*gc_strjoin3(char *s1, char *s2, char *s3,
									t_all *all);
void							free_garbage_collect(t_garbage **garbage);
void							free_garbage_env(t_garb_env **garbage_env_head);
char							*gc_strdup(char *s, t_all *all);
char							*gc_strdup_input(char *s, t_all *all);
char							*gc_strdup_env(char *s, t_all *all);
char							*gc_strjoin_env(t_all *all, char *s1, char *s2);
char							*gc_substr_env(char *s, unsigned int start,
									size_t len, t_all *all);
void							ft_lstadd_front_gc_env(t_garb_env **garbage_env,
									t_garb_env *new);
void							*gc_realloc(t_all *all, void *ptr, size_t size);
char							*gc_itoa(t_all *all, int n);
/* **********Lexing parsing************************************************** */
int								create_lexer(char *input, t_all *all);
int								pars_to_exec(t_all *all);
char							*pick_char(char *str, t_token_type type,
									t_all *all);
void							check_quotes(char c, t_all *all);
bool							as_quotes(char *str);
void							reset_quotes(t_all *all);
int								verif_quoted(char *input, t_all *all);
void							create_token(t_token_type type, char *str,
									t_all *all);
void							advance_char(t_lexer *lexr);
void							skip_whitespace(t_lexer *lexr);
int								new_tkn_char(t_token_type type, t_all *all);
void							ft_tknadd_back(t_token **lst, t_token *tkn);
t_token							*ft_tknlast(t_token *lst);
int								check_tkn_lst(t_all *all);
void							catch_heredoc(t_all *all);
void							initialize_hd_data(char *old, t_all *all);
void							handle_hd_expand(char *old, t_all *all);
void							hd_join_to_new(t_all *all, char *val);
void							create_redir_lst(t_all *all);
char							*find_last_hd(int pipe, t_all *all);
char							*search_pipe_redir(int pipe, t_token_type type,
									t_all *all);
void							print_node(t_token *token); //-------------------------debug
void							list_to_tab(t_all *all);
void							initialize_data(t_all *all, char *old);
void							handle_expand(char *old, t_all *all);
void							join_to_new(t_all *all, char *val);
char							*search_pipe_redir(int pipe, t_token_type type,
									t_all *all);
/* **********Exec functions************************************************** */
void							do_pipe(t_all *all);
int								do_no_pipe(t_all *all);
int								do_redir_fd(t_all *all);
void							fd_back_origin(t_all *all, int stdout_original,
									int stdin_original);
void							close_fd_and_hd_fd(t_all *all, int i);
int								exec_cmd(t_all *all);
char							*search_good_path(char **paths, t_all *all);
char							**do_char_env(t_all *all);
int								exec_part(t_all *all);
void							alloc_my_pipe_fd(t_all *all);
void							alloc_my_herdoc_fd(t_all *all);
int								error_dup2(t_all *all, int fd, char *redir);
int								error_dup2(t_all *all, int fd, char *redir);
int								error_msg_no_pipe(t_all *all, char *s);
void							error_msg(t_all *all, char *s);
/* **********Signal functions************************************************ */
void							signals_swing(void);
void							set_up_sig_exec(void);
/* **********Built_in functions********************************************** */
int								is_built_in(t_all *all);
int								do_built_in(t_all *all);
int								do_echo(t_all *all, char ***args, int pipe);
void							do_env(t_all *all, char **env);
char							**do_char_env(t_all *all);
void							print_node_env(t_all *all, t_env *env);
void							free_env(t_env **env);
void							do_export(t_all *all);
void							do_add_env_next(t_all *all, char *s);
void							do_add_env(t_all *all);
int								do_exit(t_all *all);
void							im_a_child(t_all *all);
int								ft_str_digit(char *str);
void							print_export(t_export *export);
void							ft_lstadd_back_export(t_export **export,
									t_export *new);
void							copy_list(t_all *all);
void							sort_list(t_all *all);
int								search_env(t_all *all, char *name);
int								replace_env(t_all *all, char *name,
									char *value);
void							replace_or_add_env(t_all *all, char *name,
									char *value);
int								is_alpha_str(char *str);
void							sort_list(t_all *all);
void							add_value_env(t_all *all, char *s);
void							print_and_null(t_all *all, char *s);
void							do_unset(t_all *all);
void							do_pwd(t_all *all);
void							do_cd(t_all *all);
char							*do_valid_s(t_all *all, char *s);
void							test_the_path(t_all *all, char *s);
void							test_the_path_mini(t_all *all, char *s);
char							*replace_until_the_last(t_all *all, char *s,
									int c);
char							*find_the_value(t_all *all, char *name);
char							*ft_pwd(t_all *all);

#endif /* MINISHELL_H */
