/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yushsato <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 18:42:51 by yushsato          #+#    #+#             */
/*   Updated: 2023/12/07 17:27:12 by yushsato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	size_t	len1;
	size_t	len2;
	char	*ret;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	ret = (char *)ft_calloc(len1 + len2 + 1, sizeof(char));
	if (!ret)
		return (0);
	ft_bzero(ret, len1 + len2 + 1);
	ft_memcpy(ret, s1, len1);
	ft_memcpy(ret + len1, s2, len2);
	return (ret);
}
