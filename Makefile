# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdsiurds <mdsiurds@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/14 13:52:45 by mdsiurds          #+#    #+#              #
#    Updated: 2025/04/18 16:22:48 by mdsiurds         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
SRC =	minishell.c \
		utils/ft_exit.c \
		utils/ft_lst.c \
		utils/ft_garbage.c \
		built_in/env/do_env.c
#		built_in/cd/do_cd.c \
		built_in/exit/do_exit.c \
		built_in/exit/do_export.c \
		built_in/pwd/do_pwd.c \
		built_in/unset/do_unset.c \



OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)
OBJ_DIR = ./temp
CC = cc
INCLUDES = -I./mandatory
CFLAGS = -Wall -Wextra -Werror -g3 $(INCLUDES)
LIBFT_DIR = ./libft
LIBFT_LIB = ./libft/libft.a
VALGRIND_FLAGS = -s --leak-check=full --show-leak-kinds=all --track-origins=yes\
--trace-children=yes --suppressions=valgrind.supp --gen-suppressions=all\
--track-fds=yes

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT_LIB)
		@echo "Compiling Minishell..."
		@$(CC) $(CFLAGS) $(OBJ) $(LIBFT_LIB) -lreadline -o $(NAME)
		@echo "Minishell successfully compiled.\n"

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@
	
	
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)/built_in
	@mkdir -p $(OBJ_DIR)/built_in/env
	@mkdir -p $(OBJ_DIR)/utils

$(LIBFT_LIB): 
	@echo	"Compiling libft..."
	@make -C $(LIBFT_DIR) >/dev/null 2>&1
	@echo "Libft successfully compiled."
clean:
	@echo	"Cleaning..."
	@rm -rf $(OBJ)
	@make -C $(LIBFT_DIR) clean >/dev/null 2>&1
	@echo	"Successfully cleaned !\n"
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -rf $(NAME)
	@make -C $(LIBFT_DIR) fclean >/dev/null 2>&1
	
re: fclean all


valgrind: fclean $(NAME)
	@echo "Running Valgrind with $(NAME)..."
	@valgrind $(VALGRIND_FLAGS) ./$(NAME)

.PHONY: all clean fclean re 