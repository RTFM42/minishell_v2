# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nsakanou <nsakanou@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/13 14:42:14 by yushsato          #+#    #+#              #
#    Updated: 2024/07/15 15:01:09 by nsakanou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell
CC		= cc
CFLAGS	= -Wall -Wextra -Werror
SRCS	= ./src/builtin/cd.c \
		  ./src/builtin/echo.c \
		  ./src/builtin/env.c \
		  ./src/builtin/pwd.c \
		  ./src/builtin/export.c \
		  ./src/builtin/unset.c \
		  ./src/env/env_obj.c \
		  ./src/env/env_raw.c \
		  ./src/execute/async.c \
		  ./src/execute/builtin_injection.c \
		  ./src/execute/exec.c \
		  ./src/execute/promise.c \
		  ./src/execute/run.c \
		  ./src/lexer/error.c \
		  ./src/lexer/lexer.c \
		  ./src/lexer/sanitizer.c \
		  ./src/lexer/token.c \
		  ./src/lexer/tokenizer.c \
		  ./src/main.c \
		  ./src/node/node.c \
		  ./src/node/node_redirection.c \
		  ./src/node/node_redirection_heredoc.c \
		  ./src/node/strsallocat.c \
		  ./src/node/token.c \
		  ./src/parser/isenvchar.c \
		  ./src/parser/parser.c \
		  ./src/parser/strallocat.c \
		  ./src/parser/word.c \
		  ./src/parser/word_env.c \
		  ./src/path.c \
		  ./src/prompt.c \
		  ./src/readline.c \
		  ./src/signal.c \
		  ./src/signal_cache.c
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
