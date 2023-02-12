NAME=			minishell
FLAGS=			-Wall -Werror -Wextra
CC=				cc
HEADERS=		includes/header.h
SRC_DIR=		src
SRC_FILES=		main.c \
				src/signals.c \
				src/tokenizer.c \
				src/syntax_checker.c \
				src/expander.c \
				src/parser.c \
				src/lib/memory.c \
				src/lib/strings.c
OBJ_FILES=		$(SRC_FILES:.c=.o)
READLINE=		/Users/bel-amri/.brew/opt/readline/


all: $(NAME)
	./minishell

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