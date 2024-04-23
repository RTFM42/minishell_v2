/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sf_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yushsato <yushsato@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 19:34:51 by yushsato          #+#    #+#             */
/*   Updated: 2024/04/23 22:17:41 by yushsato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

/**
 * ## Nullable strdup
 * @param	s1 nullable string
 * @return	NULL or copied string
*/
char	*sf_strdup(const char *s1)
{
	size_t	len;
	char	*ret;

	if (s1 == NULL)
		return (NULL);
	len = ft_strlen(s1) + sizeof(char);
	ret = (char *)sf_calloc(len, 1);
	if (!ret)
		return (NULL);
	ft_memcpy(ret, s1, len);
	return (ret);
}
