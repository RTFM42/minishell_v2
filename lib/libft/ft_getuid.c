/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getuid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yushsato <yushsato@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 14:45:45 by yushsato          #+#    #+#             */
/*   Updated: 2024/05/18 15:38:50 by yushsato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"
#include <stdio.h>
#include <unistd.h>

static void	un_getuid(unsigned int uid)
{
	(void)uid;
}

unsigned int	ft_getuid(void)
{
	unsigned int		uid;

	asm (
		"bl _getuid\n"
		"mov %w0, w0\n"
		: "=r" (uid)
		:
		: "w0", "cc"
		);
	un_getuid(uid);
	return (uid);
}
