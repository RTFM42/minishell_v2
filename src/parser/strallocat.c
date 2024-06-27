/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strallocat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yushsato <yushsato@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 01:06:57 by yushsato          #+#    #+#             */
/*   Updated: 2024/06/25 20:11:42 by yushsato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*strallocat(char *dst, const char *add, int len)
{
	int		dlen;
	char	*ret;

	dlen = 0;
	if (dst)
		dlen = ft_strlen(dst);
	ret = sf_calloc(dlen + len + 1, sizeof(char));
	if (dst)
		ft_memcpy(ret, dst, dlen);
	ft_memcpy(ret + dlen, add, len);
	if (dst)
		free(dst);
	return (ret);
}
