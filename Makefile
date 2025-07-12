# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maxoph <maxoph@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/14 13:52:45 by mdsiurds          #+#    #+#              #
#    Updated: 2025/07/12 14:59:26 by maxoph           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
SRC =	mandatory/minishell.c \
		utils/ft_exit.c \
		utils/ft_lst.c \
		utils/ft_garbage.c \
		utils/ft_garbage_env.c\
		utils/gc_itoa.c\
		built_in/env/do_env.c \
		built_in/env/do_env_utils.c \
		pipe/pipe.c\
		pipe/do_pipe.c\
		pipe/do_no_pipe.c\
		pipe/begin_exec.c\
		pipe/alloc.c\
		pipe/error.c\
		pipe/fd_back.c\
		pipe/exec_utils.c\
		parsing/expand.c\
		parsing/expand_utils.c\
		parsing/lex_pars.c\
		parsing/lexer_utils.c\
		parsing/parsing_utils.c\
		parsing/quotes_utils.c\
		parsing/redir_list.c\
		parsing/catch_heredoc.c\
		parsing/heredoc_utils.c\
		parsing/expand_heredoc.c\
		parsing/token_utils.c\
		parsing/list_to_tab.c\
		built_in/cd/do_cd.c \
		built_in/cd/cd_utils.c \
		built_in/pwd/do_pwd.c \
		built_in/is_built_in.c\
		built_in/echo/do_echo.c\
		built_in/unset/do_unset.c \
		built_in/export/do_export.c\
		built_in/export/utils_export.c\
		built_in/export/utils2_export.c\
		built_in/export/print_and_assign.c\
		built_in/export/swap_sort_print.c\
		utils/gc_split.c\
		utils/gc_strjoin.c\
		utils/ft_strcmp.c\
		signals/signals.c\
		built_in/exit/do_exit.c\
		built_in/exit/exit_utils.c



OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)
OBJ_DIR = ./temp
CC = cc
INCLUDES = -I./mandatory
CFLAGS = -Wall -Wextra -Werror $(INCLUDES) -g3 #-fsanitize=address
LIBFT_DIR = ./libft
LIBFT_LIB = ./libft/libft.a
VALGRIND_FLAGS = -s --leak-check=full --show-leak-kinds=all --track-origins=yes\
--trace-children=yes --suppressions=config_valgrind/valgrind.supp \
--gen-suppressions=all --track-fds=yes

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT_LIB)
		@echo "Compiling Minishell..."
		@$(CC) $(CFLAGS) $(OBJ) $(LIBFT_LIB) -lreadline -o $(NAME)
		@echo "Minishell successfully compiled."

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@
	
	
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)/built_in
	@mkdir -p $(OBJ_DIR)/built_in/env
	@mkdir -p $(OBJ_DIR)/built_in/cd
	@mkdir -p $(OBJ_DIR)/built_in/echo
	@mkdir -p $(OBJ_DIR)/built_in/export
	@mkdir -p $(OBJ_DIR)/built_in/unset
	@mkdir -p $(OBJ_DIR)/built_in/exit
	@mkdir -p $(OBJ_DIR)/built_in/pwd
	@mkdir -p $(OBJ_DIR)/utils
	@mkdir -p $(OBJ_DIR)/mandatory
	@mkdir -p $(OBJ_DIR)/parsing
	@mkdir -p $(OBJ_DIR)/pipe
	@mkdir -p $(OBJ_DIR)/signals
	

$(LIBFT_LIB): 
	@echo	"Compiling libft..."
	@make -C $(LIBFT_DIR) >/dev/null 2>&1
	@echo "Libft successfully compiled."
clean:
	@echo	"Cleaning..."
	@rm -rf $(OBJ)
	@make -C $(LIBFT_DIR) clean >/dev/null 2>&1
	@echo	"Successfully cleaned !"
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -rf $(NAME)
	@make -C $(LIBFT_DIR) fclean >/dev/null 2>&1
	
re: fclean all


valgrind: fclean $(NAME)
	@echo "Running Valgrind with $(NAME)..."
	@valgrind $(VALGRIND_FLAGS) ./$(NAME)

.PHONY: all clean fclean re valgrind