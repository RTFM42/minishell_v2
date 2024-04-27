# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yushsato <yushsato@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/13 14:42:14 by yushsato          #+#    #+#              #
#    Updated: 2024/04/26 22:05:59 by yushsato         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell
CC		= cc
CFLAGS	= -Wall -Wextra -Werror
SRCS	= ./src/main.c \
		  ./src/env_obj.c \
		  ./src/env_raw.c \
		  ./src/prompt.c \
		  ./src/readline.c \
		  ./src/signal.c

OBJS	= $(SRCS:.c=.o)
RLDIR	= $(shell brew --prefix readline)
LIBFT	= libft.a
PRINTF	= libftprintf.a
RLFLAGS	=  -L$(RLDIR)/lib -lreadline
INCLUDE	= -I./ -I./src -I$(RLDIR)/include

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(NAME): $(OBJS) $(LIBFT) $(PRINTF)
	$(CC) $(CFLAGS) $^ -o $@ $(INCLUDE) $(RLFLAGS)

$(LIBFT):
	cd lib          && \
	cd libft        && \
	make all        && \
	cp $@ ../../

$(PRINTF):
	cd lib          && \
	cd printf       && \
	make all        && \
	cp $@ ../../

readline:
	brew list readline &> /dev/null || brew install readline

all: readline $(LIBFT) $(PRINTF) $(NAME)

clean:
	rm -rf $(OBJS) $(LIBFT) $(PRINTF)
	cd lib && cd libft && make clean
	cd lib && cd printf && make clean

fclean: clean
	rm -f $(NAME)
	cd lib && cd libft && make fclean
	cd lib && cd printf && make fclean

re: fclean all

__debug_configure__:
	$(eval CC := gcc)
	$(eval CFLAGS := -g -fsanitize=address -Wall -Wextra -Werror)

debug: __debug_configure__ all

norminette: $(SRCS)
	norminette $^ minishell.h

norm: norminette

.PHONY: all clean fclean re debug norminette norm