/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sf_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yushsato <yushsato@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 18:51:27 by yushsato          #+#    #+#             */
/*   Updated: 2024/04/13 22:33:32 by yushsato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "unistd.h"

void	*sf_calloc(size_t count, size_t size)
{
	void	*ptr;

	if (count && size && size > SIZE_MAX / count)
		return (0);
	if (count == 0 || size == 0)
	{
		count = 1;
		size = 1;
	}
	ptr = malloc(size * count);
	if (ptr == NULL)
	{
		write(2, "-minishell: malloc: Cannot allocate memory.\n", 44);
		exit(1);
	}
	if (ptr)
		ft_bzero(ptr, size * count);
	return (ptr);
}
