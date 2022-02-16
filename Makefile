SHELL = /bin/sh
NAME = minishell
FILES = main.c

CC = cc
FLAGS = -Wall -Werror -Wextra -fsanitize=address -g3
RM = rm -rf

OBJS = $(FILES:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) -c $(OBJS) -o $@

%.o:%.c
	$(CC) $(FLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

.PHONY: all clean fclean re