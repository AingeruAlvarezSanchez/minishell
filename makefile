CC				= gcc
NAME			= minishell
LIBFT			= include/Libft/
INCLUDE			= /include/minishell.h
LIB				= include/Libft/libft.a
READLINE_PATH	= ~/.brew/opt/readline
READLINE		= -I$(READLINE_PATH)/include -lreadline -L $(READLINE_PATH)/lib
FLAGS			=  -Wall -Wextra -Werror -g #-fsanitize=address -g3
OBJS			= $(SRCS:.c=.o)

all: $(NAME)

SRCS			= src/main.c									\
				src/utils/errors.c								\
				src/utils/utils.c								\
				src/utils/utils2.c								\
				src/utils/frees.c								\
				src/builtins/unset.c							\
				src/builtins/export.c							\
				src/builtins/export_uninit.c					\
				src/builtins/echo.c								\
				src/builtins/cd.c								\
				src/builtins/pwd.c								\
				src/builtins/env.c								\
				src/builtins/exit.c								\
				src/builtins/builtins.c							\
				src/exec/parser.c								\
				src/exec/execute.c								\
				src/exec/binary.c								\
				src/signals/signals.c							\
				src/specials/specials.c							\
				src/specials/dollars.c							\
                src/specials/dollar_val.c						\

$(NAME) : $(OBJS)
	@echo "Compiling"
	make -C $(LIBFT)
	@$(CC) $(FLAGS) -o $(NAME) $(OBJS) $(LIB) $(READLINE)
	@echo "Compilation done"

%.o: %.c
	@${CC} ${FLAGS} -c $< -o $@

clean:
	make fclean -C $(LIBFT)
	$(RM) ./*/*/*.o
	$(RM) $(OBJS)
	@echo "clean done"

fclean: clean
	@$(MAKE) fclean -C include/Libft/
	$(RM) $(OBJS)
	$(RM) $(NAME)
	@rm -rf .DS_Store
	@rm -rf .vscode
	@rm -rf minishell.dSYM
	@echo "fclean done"

re: clean all

.PHONY: all clean fclean re

