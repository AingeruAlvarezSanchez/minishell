SHELL = /bin/sh
NAME = minishell
CC		=	gcc
RM		=	rm -rf
FLAGS	=	-Wall -Wextra -Werror -g #-fsanitize=address -g3
SRC		=	main.c		\
			commands.c			\
			execute.c			\
			builtins/echo.c		\
			builtins/pwd.c		\
			builtins/env.c		\
			builtins/cd.c		\
			builtins/exit.c		\
			builtins/export.c
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

.PHONY: all clean fclean re all
