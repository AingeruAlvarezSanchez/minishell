SHELL = /bin/sh
NAME = minishell
CC		=	gcc
RM		=	rm -rf
FLAGS	=	-Wall -Wextra -Werror -g -lreadline -g3 #-fsanitize=address
SRC		=	main.c
LIB		=	libft/libft.a

$(NAME): all

all: $(SRC)
	@$(MAKE) -C libft/
	@ $(CC) $(FLAGS) $(SRC) $(LIB) -o $(NAME)
	@ echo "compilation OK"

clean:

	$(RM) $(NAME)
	$(RM) libft/*.o
	@ echo "clean done"

fclean: clean
	@$(RM) minishell.dSYM
	@$(RM) minishell
	@$(MAKE) clean -C libft/
	@ echo "fclean done"

re: clean all

.PHONY: all clean fclean re all