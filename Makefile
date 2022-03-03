SHELL = /bin/sh
NAME = minishell
CC		=	gcc
RM		=	rm -rf
FLAGS	=	-Wall -Wextra -Werror -g  -g3 -fsanitize=address
SRC		=	src/main.c	\
			src/echo.c	\
			src/pwd.c	\
			src/env.c	\
			src/cd.c	\
			src/exit.c	\
			src/quotes.c\
			src/export.c\
			src/commands.c

INCLUDE =	inc/minishell.h
LIB		=	libft/libft.a

$(NAME): all

all: $(SRC)
	@$(MAKE) -C libft/
	@ $(CC) $(FLAGS) $(SRC) $(INCLUDE) $(LIB) -lreadline -o $(NAME)
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
