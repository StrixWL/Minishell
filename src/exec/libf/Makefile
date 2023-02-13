CC=cc
FLAGS= -Wall -Werror -Wextra
AR=ar cr
RM=rm -rf
FILES= ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_strlen.c \
	   ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c ft_strncmp.c \
	   ft_strnstr.c ft_strlcpy.c ft_strlcat.c ft_atoi.c ft_strdup.c \
	   ft_substr.c ft_strjoin.c ft_split.c ft_itoa.c ft_strmapi.c \
	   ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_isprint.c \
	   ft_putnbr_fd.c ft_strtrim.c ft_memcpy.c ft_memmove.c ft_memset.c \
	   ft_memcmp.c ft_memchr.c ft_bzero.c ft_calloc.c ft_striteri.c
BFILES  = ft_lstnew.c ft_lstadd_front.c\
	   ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c \
	   ft_lstclear.c ft_lstiter.c ft_lstmap.c
OBJ=$(FILES:.c=.o)
BOBJ=$(BFILES:.c=.o)
NAME=libft.a

.PHONY: all bonus clean fclean re

all: $(NAME)

bonus: all $(BOBJ)
	$(AR) $(NAME) $(BOBJ)

$(NAME): $(OBJ)
	$(AR) $(NAME) $(OBJ)

%.o: %.c libft.h
	$(CC) $(FLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ) $(BOBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all
