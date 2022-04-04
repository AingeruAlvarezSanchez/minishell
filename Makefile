SHELL = /bin/sh
NAME = minishell
CC		=	gcc
RM		=	rm -rf
FLAGS	=	-Wall -Wextra -Werror -g  -g3 -fsanitize=address
SRC		=	src/main.c				\
			src/initials.c			\
			src/quotes.c			\
			src/dollars.c			\
			src/pipes.c				\
			src/parsing.c			\
			src/signals.c			\
			src/check_builtins.c	\
			src/builtins/exit.c		\
			src/builtins/cd.c		\
			src/builtins/export.c	\
			src/builtins/unset.c

INCLUDE =	inc/minishell.h
LIB		=	libft/libft.a

$(NAME): all

all: $(SRC)
	@$(MAKE) -C libft/
	@ $(CC) $(FLAGS) $(SRC) $(LIB) -lreadline -o $(NAME)
	@ echo "compilation OK"

clean:
	@$(RM) libft/*.o
	@$(RM) *.o
	@ echo "clean done"

fclean: clean
	@$(MAKE) fclean -C libft/
	@$(RM) minishell.dSYM
	@$(RM) $(NAME)
	@ echo "fclean done"

re: clean all

.PHONY: all clean fclean re