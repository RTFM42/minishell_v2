# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yushsato <yushsato@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/13 14:42:14 by yushsato          #+#    #+#              #
#    Updated: 2024/06/11 01:57:16 by yushsato         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell
CC		= cc
CFLAGS	= -Wall -Wextra -Werror
SRCS	= ./src/env/env_obj.c \
		  ./src/env/env_raw.c \
		  ./src/execute/execute.c \
		  ./src/lexer/lexer.c \
		  ./src/lexer/token.c \
		  ./src/lexer/tokenizer.c \
		  ./src/parser/isenvchar.c \
		  ./src/parser/parser.c \
		  ./src/parser/sanitize.c \
		  ./src/parser/strallocat.c \
		  ./src/parser/word.c \
		  ./src/main.c \
		  ./src/path.c \
		  ./src/prompt.c \
		  ./src/readline.c \
		  ./src/signal.c \

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

debug: fclean __debug_configure__ all

norminette: $(SRCS)
	norminette $^ minishell.h

norm: norminette

.PHONY: all clean fclean re debug norminette norm
