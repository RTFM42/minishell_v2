/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yushsato <yushsato@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 10:42:00 by yushsato          #+#    #+#             */
/*   Updated: 2024/04/13 17:26:29 by yushsato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strnjoin(const char *s1, const char *s2, int n2)
{
	size_t	len1;
	char	*ret;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	ret = (char *)ft_calloc(len1 + n2 + 1, sizeof(char));
	if (!ret)
		return (0);
	ft_memcpy(ret, s1, len1);
	ft_memcpy(ret + len1, s2, n2);
	return (ret);
}
