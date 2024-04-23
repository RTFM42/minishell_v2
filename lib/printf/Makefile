# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yushsato <yushsato@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/12 20:23:39 by yushsato          #+#    #+#              #
#    Updated: 2024/04/23 21:44:08 by yushsato         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libftprintf.a
CC		= cc 
CFLAGS	= -Wall -Wextra -Werror
SRCS	= ./ft_printf.c \
		  ./ex_putchar_fd.c \
		  ./ex_putnbr_fd.c \
		  ./ex_putptr_fd.c \
		  ./ex_putstr_fd.c \
		  ./ex_putunbr_base_fd.c \
		  ./ex_putunbr_fd.c \
		  ./ex_putva_fd.c \
		  ./ex_uadd.c
#		  ./ft_memcmp.c \
#		  ./ft_putstr_fd.c \
#		  ./ft_putnbr_fd.c \
#		  ./ft_putchar_fd.c \
#		  ./ft_strlen.c
OBJS	= $(SRCS:.c=.o)
LIBFT	= libft.a
INCL	= -I./

$(NAME): $(OBJS) $(LIBFT)
	ar rcs $(NAME) $(OBJS)

$(LIBFT):
	cd ../libft      && \
	make all         && \
	cp $@ ../printf/.a

all: $(LIBFT) $(NAME)

%.o: %.c $(INCL)
	$(CC) $(CFLGS) -c $< -o $@ $(INCL)

clean:
	rm -f $(OBJS) $(LIBFT)
	cd ../libft && make clean

fclean: clean
	rm -f $(NAME)
	cd ../libft && make fclean

re: fclean all
