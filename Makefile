NAME=			minishell
FLAGS=			-Wall -Werror -Wextra -g -fsanitize=address,undefined
CC=				cc
HEADERS=		includes/header.h
SRC_DIR=		src
SRC_FILES=		main.c \
				src/signals.c \
				src/tokenizer.c \
				src/syntax_checker.c \
				src/expander.c \
				src/redirections.c \
				src/parser.c \
				src/environment.c \
				src/lib/memory.c \
				src/lib/strings.c \
				src/exec/exec.c \
				src/builtins/echo.c \
				src/builtins/pwd.c \
				src/builtins/exit.c \
				src/builtins/cd.c \
				src/builtins/unset.c \
				src/builtins/export.c \
				
OBJ_FILES=		$(SRC_FILES:.c=.o)
READLINE=		/Users/bel-amri/.brew/opt/readline/


all: $(NAME)


$(NAME): $(OBJ_FILES)
	$(CC) $(OBJ_FILES) $(FLAGS) -lreadline -L$(READLINE)/lib -o $(NAME) src/exec/libf/libft.a

%.o: %.c $(HEADERS)
	$(CC) $(FLAGS) -I$(READLINE)/include -Iincludes -c $< -o $@

norminette:
	@echo \\n\\n\\n\\n\\n & norminette ${SRC_DIR} ${INCLUDE_DIR}

clean:
	rm -f $(OBJ_FILES)

fclean: clean
	rm -f $(NAME)

re: fclean all