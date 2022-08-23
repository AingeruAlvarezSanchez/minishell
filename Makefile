SHELL = /bin/sh
NAME = minishell
CC		=	gcc
RM		=	rm -rf
FLAGS	=	-Wall -Wextra -Werror -g -g3 -fsanitize=address
FILES		=	src/main		\
			src/builtins/exit	\
			src/builtins/cd		\
			src/builtins/export	\
			src/builtins/unset	\
			src/builtins/echo	\
			src/builtins/pwd	\
			src/builtins/env	\
			src/initials		\
			src/special_chars	\
			src/firstcase		\
			src/errors			\
			src/quotes			\
			src/parsing			\
			src/pipes			\
			src/utils			\
			src/lastjoin		\
			src/execute			\
			src/signals			\
			src/composed_quotes	\
			src/dollars

INCLUDE =	inc/minishell.h
LIB		=	libft/libft.a

PWD = ~/.brew/opt/readline

READLINE =	-lreadline -L /Users/$(USER)/.brew/opt/readline/lib\
			-I /Users/$(USER)/.brew/opt/readline/include\
					
SRCS	=	$(addsuffix .c, $(FILES))
OBJS	=	$(addsuffix .o, $(FILES))

all: $(NAME)

.c.o:
	@$(CC) $(FLAGS) -c -o $@ $<

$(NAME): $(OBJS) $(SRCS)
	@$(MAKE) -C libft/
	@$(CC) $(FLAGS) $(OBJS) $(LIB) $(READLINE) -o $(NAME)
	@echo compilado ok

clean:
	@$(RM) libft/*.o
	@$(RM) src/*.o
	@$(RM) src/builtins/*.o
	@$(RM) *.o
	@ echo "clean done"

fclean: clean
	@$(MAKE) fclean -C libft/
	@$(RM) minishell.dSYM
	@$(RM) $(NAME)
	@ echo "fclean done"

re: clean all

.PHONY: all clean fclean re
