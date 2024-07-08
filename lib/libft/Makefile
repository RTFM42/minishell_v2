# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yushsato <yushsato@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/12 20:21:50 by yushsato          #+#    #+#              #
#    Updated: 2024/07/08 21:19:44 by yushsato         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC   = cc
CFLG = -Wall -Werror -Wextra
INCL = libft.h
SRCS = ./ft_atoi.c \
	   ./ft_bzero.c \
	   ./ft_calloc.c \
	   ./ft_isalnum.c \
	   ./ft_isalpha.c \
	   ./ft_isascii.c \
	   ./ft_isdigit.c \
	   ./ft_isprint.c \
	   ./ft_isspace.c \
	   ./ft_itoa.c \
	   ./ft_memchr.c \
	   ./ft_memcmp.c \
	   ./ft_memcpy.c \
	   ./ft_memmove.c \
	   ./ft_memset.c \
	   ./ft_putchar_fd.c \
	   ./ft_putendl_fd.c \
	   ./ft_putnbr_fd.c \
	   ./ft_putstr_fd.c \
	   ./ft_split.c \
	   ./ft_strchr.c \
	   ./ft_strdup.c \
	   ./ft_strictatoi.c \
	   ./ft_striteri.c \
	   ./ft_strjoin.c \
	   ./ft_strlcat.c \
	   ./ft_strlcpy.c \
	   ./ft_strlen.c \
	   ./ft_strmapi.c \
	   ./ft_strncmp.c \
	   ./ft_strnjoin.c \
	   ./ft_strnstr.c \
	   ./ft_strrchr.c \
	   ./ft_strtrim.c \
	   ./ft_substr.c \
	   ./ft_tolower.c \
	   ./ft_toupper.c \
	   ./sf_calloc.c \
	   ./sf_close.c \
	   ./sf_error.c \
	   ./sf_open.c \
	   ./sf_strdup.c

OBJS  = $(SRCS:.c=.o)
BOBJS = $(BONUS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

%.o: %.c $(INCL)
	$(CC) $(CFLG) -c $< -o $@ -I./

clean:
	rm -rf $(OBJS) $(BOBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
