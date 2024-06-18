/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strsallocat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yushsato <yushsato@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 23:31:54 by yushsato          #+#    #+#             */
/*   Updated: 2024/06/17 23:32:15 by yushsato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**strsallocat(char **ary, char *add)
{
	int		i;
	char	**head;
	char	**ret;

	head = ary;
	i = 0;
	while (ary && *ary && ++i)
		ary++;
	ret = ft_calloc(i + 2, sizeof(char *));
	ft_memcpy(ret, head, i * sizeof(char *));
	free(head);
	ret[i] = ft_strdup(add);
	return (ret);
}
