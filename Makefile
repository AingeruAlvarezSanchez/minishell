SHELL = /bin/sh
NAME = minishell
CC		=	gcc
RM		=	rm -rf
FLAGS	=	-Wall -Wextra -Werror -g -g3 -fsanitize=address
SRC		=	src/main.c				\
			src/initials.c			\
			src/special_chars.c		\
			src/firstcase.c			\
			src/errors.c			\
			src/quotes.c			\
			src/pipes.c

INCLUDE =	inc/minishell.h
LIB		=	libft/libft.a

PWD = ~/.brew/opt/readline

READLINE =	-lreadline -L /Users/$(USER)/.brew/opt/readline/lib\
			-I /Users/$(USER)/.brew/opt/readline/include\

$(NAME): all

all: $(SRC)
	@$(MAKE) -C libft/
	@ $(CC) $(FLAGS) $(SRC) $(LIB) $(READLINE) -o $(NAME)
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