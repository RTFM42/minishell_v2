/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yushsato <yushsato@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 03:51:17 by yushsato          #+#    #+#             */
/*   Updated: 2024/04/23 20:51:03 by yushsato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	set_errno(const int no)
{
	errno =	no;
	return (no);
}

void	exit_with_errno(char *name)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(name, 2);
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
	else if (errno)
	{
		ft_putstr_fd(":(", 2);
		ft_putnbr_fd(errno, 2);
		ft_putendl_fd(")Unsensitive system error.", 2);
	}
	exit(1);
}