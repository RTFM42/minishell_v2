/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yushsato <yushsato@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 18:51:27 by yushsato          #+#    #+#             */
/*   Updated: 2024/04/13 22:34:29 by yushsato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "unistd.h"

void	*ft_calloc(size_t count, size_t size)
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
	if (ptr)
		ft_bzero(ptr, size * count);
	return (ptr);
}
