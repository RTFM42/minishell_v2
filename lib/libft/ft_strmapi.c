/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yushsato <yushsato@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 18:04:34 by yushsato          #+#    #+#             */
/*   Updated: 2024/06/25 20:11:42 by yushsato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(const char *s, char (*f)(unsigned int, char))
{
	size_t	i;
	char	*ret;

	if (!s || !f)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
		i++;
	ret = sf_calloc(i + 1, sizeof(char));
	if (ret == NULL)
		return (NULL);
	i = 0;
	while (*s != '\0')
	{
		ret[i] = f(i, *s++);
		i++;
	}
	return (ret);
}
