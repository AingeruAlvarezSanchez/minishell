# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/24 12:12:22 by aalvarez          #+#    #+#              #
#    Updated: 2022/07/18 05:39:58 by aalvarez         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC = ft_isalpha.c			\
	  ft_isdigit.c			\
	  ft_isalnum.c			\
	  ft_isascii.c			\
	  ft_isprint.c			\
	  ft_strlen.c			\
	  ft_doublestrlen.c		\
	  ft_strlcpy.c			\
	  ft_strlcat.c			\
	  ft_strncmp.c			\
	  ft_toupper.c			\
	  ft_tolower.c			\
	  ft_strnstr.c			\
	  ft_num_to_binary.c	\
	  ft_atoi.c				\
	  ft_strchr.c			\
	  ft_strchr_pos.c		\
	  ft_strrchr.c			\
	  ft_memset.c			\
	  ft_bzero.c			\
	  ft_memchr.c			\
	  ft_memcmp.c			\
	  ft_memcpy.c			\
	  ft_memmove.c			\
	  ft_calloc.c			\
	  ft_strdup.c			\
	  ft_substr.c			\
	  ft_strjoin.c			\
	  ft_strtrim.c			\
	  ft_split.c			\
	  mini_split.c			\
	  mini_split_utils.c	\
	  ft_itoa.c				\
	  ft_putchar_fd.c		\
	  ft_putstr_fd.c		\
	  ft_putendl_fd.c		\
	  ft_putnbr_fd.c		\
	  ft_strmapi.c			\
	  ft_doublefree.c		\
	  ft_triplefree.c		\
	  ft_doublestrdup.c		\
	  ft_deletechar.c

SRC_BONUS = ft_lstnew.c			\
			ft_lstadd_front.c	\
			ft_lstsize.c		\
			ft_lstlast.c		\
			ft_lstadd_back.c	\
			ft_lstdelone.c		\
			ft_lstclear.c		\
			ft_lstiter.c		\
			ft_lstmap.c

INCLUDES = libft.h

OBJ_BONUS = $(SRC_BONUS:.c=.o)
OBJ = $(SRC:.c=.o)

CC = gcc
AR = ar rc
CFLAGS = #-Wall -Wextra -Werror
RM = /bin/rm -f

all: $(NAME)

$(NAME) : $(OBJ) $(INCLUDES)
	@$(AR) $(NAME) $(OBJ)

bonus: $(OBJ_BONUS) $(INCLUDES)
	@$(AR) $(NAME) $(OBJ_BONUS)

%.o : %.c
	@$(CC) $(CFLAGS) -c $(SRC) $(SRC_BONUS)

clean:
	@$(RM) $(OBJ) $(OBJ_BONUS)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
