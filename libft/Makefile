# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdsiurds <mdsiurds@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/18 15:54:09 by mdsiurds          #+#    #+#              #
#    Updated: 2025/05/08 19:59:31 by mdsiurds         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC = ./libft/ft_bzero.c ./libft/ft_isalnum.c ./libft/ft_isalpha.c ./libft/ft_isascii.c ./libft/ft_isdigit.c ./libft/ft_isprint.c \
	./libft/ft_memcpy.c ./libft/ft_memmove.c ./libft/ft_memset.c ./libft/ft_strlen.c ./libft/ft_strlcpy.c ./libft/ft_strlcat.c \
	./libft/ft_toupper.c ./libft/ft_tolower.c ./libft/ft_strchr.c ./libft/ft_strrchr.c ./libft/ft_strncmp.c ./libft/ft_memchr.c \
	./libft/ft_memcmp.c ./libft/ft_strnstr.c ./libft/ft_atoi.c ./libft/ft_calloc.c ./libft/ft_strdup.c ./libft/ft_substr.c \
	./libft/ft_strjoin.c ./libft/ft_strtrim.c ./libft/ft_split.c ./libft/ft_itoa.c ./libft/ft_strmapi.c ./libft/ft_striteri.c \
	./libft/ft_putchar_fd.c ./libft/ft_putstr_fd.c ./libft/ft_putendl_fd.c ./libft/ft_putnbr_fd.c \
	./printf/ft_hexa.c ./printf/ft_pointer.c ./printf/ft_printf.c ./printf/ft_putchar.c ./printf/ft_putnbr.c \
	./printf/ft_putstr.c ./printf/ft_strlcpy.c ./printf/ft_strlen.c ./printf/ft_unsigned.c \
	./gnl/get_next_line.c ./gnl/get_next_line_utils.c
	
OBJ = $(SRC:.c=.o)
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
AR = ar rcs

all: $(NAME)

$(NAME): $(OBJ)
	$(AR) $(NAME) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
.PHONY: all clean fclean re 