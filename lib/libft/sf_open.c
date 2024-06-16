/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sf_open.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yushsato <yushsato@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 14:44:11 by yushsato          #+#    #+#             */
/*   Updated: 2024/06/14 16:29:26 by yushsato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <sys/types.h>
#include <sys/stat.h>

int	sf_error_print(const char *name);

int	sf_fopen(const char *path, int flag)
{
	const int	fd = open(path, flag);

	if (fd < -1)
		ERR().print(path);
	return (fd);
}
