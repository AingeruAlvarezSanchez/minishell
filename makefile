CC				= gcc
NAME			= minishell
LIBFT			= include/Libft/
INCLUDE			= /include/minishell.h
LIB				= include/Libft/libft.a
READLINE_PATH	= ~/.brew/opt/readline
READLINE		= -I$(READLINE_PATH)/include -lreadline -L $(READLINE_PATH)/lib
FLAGS			=  -Wall -Wextra -Werror -g -fsanitize=address -g3

SRCS			= src/main.c									\
				src/environment/environment.c					\
				src/parser/parser.c								\
				src/errors/error.c								\
				src/errors/string_errors.c						\
				src/specials/redir.c							\
				src/utils/utils.c								\
				src/utils/free_things.c							\
				src/dollars/dollars.c							\
				src/dollars/dollar_value.c						\
				src/builtins/unset.c							\
				src/builtins/export.c							\
				src/builtins/export_utils.c						\
				src/builtins/echo.c								\
				src/builtins/cd.c								\
				src/builtins/cd_utils.c							\
				src/builtins/pwd.c								\
				src/builtins/env.c								\
				src/builtins/exit.c								\
				src/builtins/check_builtins.c					\
				src/execution/execute.c							\
				src/execution/binary_manage.c					\
				src/execution/binary_manage_utils.c				\
				src/signals/signals.c							\
				src/specials/pipes.c							\
				src/specials/quotes.c							\

OBJS	= $(SRCS:.c=.o)

all: $(NAME)

.SILENT:

$(NAME) : $(OBJS)
	echo "Compiling"
	make -C $(LIBFT)
	@$(CC) $(FLAGS) -o $(NAME) $(OBJS) $(LIB) $(READLINE)
	echo "Compilation done"

%.o: %.c
	@${CC} ${FLAGS} -c $< -o $@

clean:
	make fclean -C $(LIBFT)
	$(RM) ./*/*/*.o
	$(RM) $(OBJS)
	echo "clean done"

fclean: clean
	$(MAKE) fclean -C include/Libft/
	$(RM) $(OBJS)
	$(RM) $(NAME)
	rm -rf .DS_Store
	rm -rf .vscode
	rm -rf minishell.dSYM
	echo "fclean done"

re: clean all

.PHONY: all clean fclean re

