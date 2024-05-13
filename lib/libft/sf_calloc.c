/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sf_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yushsato <yushsato@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 18:51:27 by yushsato          #+#    #+#             */
/*   Updated: 2024/05/14 07:46:31 by yushsato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <errno.h>
#include "libft.h"
#include "unistd.h"

/**
 * ## Safety calloc
 * @note	if failed to allocate memory, this function display reason and exit.
 * @param	count count
 * @param	size memory size
 * @return	allocated memory pointer
*/
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
		(ERR().exit)(__func__, 1);
	if (ptr)
		ft_bzero(ptr, size * count);
	return (ptr);
}
