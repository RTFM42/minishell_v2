# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yushsato <yushsato@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/13 14:42:14 by yushsato          #+#    #+#              #
#    Updated: 2024/04/15 04:19:29 by yushsato         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell
CC		= cc
CFLAGS	= -Wall -Wextra -Werror
SRCS	= ./src/main.c \
		  ./src/env.c \
		  ./src/error.c \
		  ./src/prompt.c \
		  ./src/readline.c \
		  ./src/signal.c

OBJS	= $(SRCS:.c=.o)
RLDIR	= $(shell brew --prefix readline)
LIBFT	= libft.a
RLFLAGS	=  -L$(RLDIR)/lib -lreadline
INCLUDE	= -I./ -I./src -I$(RLDIR)/include

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $^ -o $@ $(INCLUDE) $(RLFLAGS)

$(LIBFT):
		cd lib          && \
		cd libft        && \
		make all        && \
		cp $@ ../../    && \
		make fclean

readline:
	brew install readline

all: readline $(NAME)

clean:
	rm -rf $(OBJS) $(LIBFT)

fclean: clean
	rm -f $(NAME)

re: fclean all

build: all clean

__debug_configure__:
	$(eval CC := gcc)
	$(eval CFLAGS := -g -fsanitize=address -Wall -Wextra -Werror)

debug: __debug_configure__ all

norminette: $(SRCS)
	norminette $^ minishell.h

norm: norminette

.PHONY: all clean fclean re build debug norminette norm