# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bel-amri <clorensunity@gmail.com>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/21 09:14:44 by yabidi            #+#    #+#              #
#    Updated: 2023/02/21 14:20:47 by bel-amri         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=			minishell
FLAGS=			-Wall -Werror -Wextra -g -fsanitize=address,undefined
CC=				cc
HEADERS=		includes/header.h
SRC_DIR=		src
SRC_FILES=		main.c \
				src/tokenizer.c \
				src/syntax_checker.c \
				src/signals.c \
				src/expander.c \
				src/redirections.c \
				src/parser.c \
				src/environment.c \
				src/lib/memory.c \
				src/lib/strings.c \
				src/exec/exec.c \
				src/exec/exec2.c \
				src/exec/exec3.c \
				src/exec/exec4.c \
				src/builtins/echo.c \
				src/builtins/pwd.c \
				src/builtins/exit.c \
				src/builtins/cd.c \
				src/builtins/cd2.c \
				src/builtins/unset.c \
				src/builtins/export.c \
				src/builtins/export2.c \
				src/exec/libf/ft_isalpha.c src/exec/libf/ft_isdigit.c src/exec/libf/ft_isalnum.c src/exec/libf/ft_isascii.c src/exec/libf/ft_strlen.c \
	   src/exec/libf/ft_toupper.c src/exec/libf/ft_tolower.c src/exec/libf/ft_strchr.c src/exec/libf/ft_strrchr.c src/exec/libf/ft_strncmp.c \
	   src/exec/libf/ft_strnstr.c src/exec/libf/ft_strlcpy.c src/exec/libf/ft_strlcat.c src/exec/libf/ft_atoi.c src/exec/libf/ft_strdup.c \
	   src/exec/libf/ft_substr.c src/exec/libf/ft_strjoin.c src/exec/libf/ft_split.c src/exec/libf/ft_itoa.c src/exec/libf/ft_strmapi.c \
	   src/exec/libf/ft_putchar_fd.c src/exec/libf/ft_putstr_fd.c src/exec/libf/ft_putendl_fd.c src/exec/libf/ft_isprint.c \
	   src/exec/libf/ft_putnbr_fd.c src/exec/libf/ft_strtrim.c src/exec/libf/ft_memcpy.c src/exec/libf/ft_memmove.c src/exec/libf/ft_memset.c \
	   src/exec/libf/ft_memcmp.c src/exec/libf/ft_memchr.c src/exec/libf/ft_bzero.c src/exec/libf/ft_calloc.c src/exec/libf/ft_striteri.c
				
OBJ_FILES=		$(SRC_FILES:.c=.o)
READLINE=		/Users/bel-amri/.brew/opt/readline/


all: $(NAME)


$(NAME): $(OBJ_FILES)
	$(CC) $(OBJ_FILES) $(FLAGS) -lreadline -L$(READLINE)/lib -o $(NAME) 

%.o: %.c $(HEADERS)
	$(CC) $(FLAGS) -I$(READLINE)/include -Iincludes -c $< -o $@

norminette:
	@echo \\n\\n\\n\\n\\n & norminette ${SRC_DIR} ${INCLUDE_DIR}

clean:
	rm -f $(OBJ_FILES)

fclean: clean
	rm -f $(NAME)

re: fclean all