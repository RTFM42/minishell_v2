/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sf_close.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yushsato <yushsato@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 02:10:16 by yushsato          #+#    #+#             */
/*   Updated: 2024/06/19 16:26:03 by yushsato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

int	sf_error_print(const char *name);

int	sf_close(int fd)
{
	const int	err = close(fd);

	if (err < 0)
		sf_error_print("close");
	return (err);
}
