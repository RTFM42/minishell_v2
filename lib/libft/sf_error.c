/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sf_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yushsato <yushsato@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 22:04:31 by yushsato          #+#    #+#             */
/*   Updated: 2024/06/14 16:19:56 by yushsato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include "libft.h"
#include "stdlib.h"
#include "stdio.h"

/**
 * ## Display error and exit with status 1
 * @param	name originating function name, etc.
 * 					for the most part, just write `__func__`.
 * @param	num exit number.
 * @return	1
*/
void	sf_error_exit(const char *name, int num)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd((char *)name, 2);
	if (errno == EACCES)
		ft_putendl_fd(": Permission denied.", 2);
	else if (errno == EEXIST)
		ft_putendl_fd(": File exists.", 2);
	else if (errno == EINVAL)
		ft_putendl_fd(": Invalid argument.", 2);
	else if (errno == ENOENT)
		ft_putendl_fd(": No such file or directory.", 2);
	else if (errno == ENOMEM)
		ft_putendl_fd(":Not enough space/cannot allocate memory.", 2);
	else if (errno == EIO)
		ft_putendl_fd(": Remote I/O error.", 2);
	else
	{
		ft_putstr_fd(":(", 2);
		ft_putnbr_fd(errno, 2);
		ft_putendl_fd(")Unsensitive system error.", 2);
	}
	exit(num);
}

/**
 * ## Display error && Return status (0 or 1)
 * @param	name originating function name, etc.
 * 					for the most part, just write `__func__`.
 * @return	0/1
*/
int	sf_error_print(const char *name)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd((char *)name, 2);
	if (errno == EACCES)
		ft_putendl_fd(":Permission denied.", 2);
	else if (errno == EEXIST)
		ft_putendl_fd(":File exists.", 2);
	else if (errno == EINVAL)
		ft_putendl_fd(":Invalid argument.", 2);
	else if (errno == ENOENT)
		ft_putendl_fd(":No such file or directory.", 2);
	else if (errno == ENOMEM)
		ft_putendl_fd(":Not enough space/cannot allocate memory.", 2);
	else if (errno == EIO)
		ft_putendl_fd(":Remote I/O error.", 2);
	else
	{
		ft_putstr_fd(":(", 2);
		ft_putnbr_fd(errno, 2);
		ft_putendl_fd(")Unsensitive error.", 2);
	}
	return (1);
}

/**
 * ## Set errno
 * @param	no error number
 * @return	param value
*/
int	sf_error_setno(const int no)
{
	errno = no;
	return (no);
}

t_errc	err_constructor(void)
{
	static const t_errc	errc = {
		.exit = sf_error_exit,
		.print = sf_error_print,
		.setno = sf_error_setno,
	};

	return (errc);
}
