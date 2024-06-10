/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yushsato <yushsato@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 17:04:16 by yushsato          #+#    #+#             */
/*   Updated: 2024/06/10 19:28:29 by yushsato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// char	**arypush(char **ary, char *add)
// {
// 	int		i;
// 	char	**head;
// 	char	**ret;

// 	head = ary;
// 	i = 0;
// 	while (head && *head && ++i)
// 		head++;
// 	ret = ft_calloc(i + 2, sizeof(char *));
// 	head = ary;
// 	ft_memcpy(ret, ary, i * sizeof(char *));
// 	free(ary);
// 	ret[i] = add;
// 	return (ret);
// }

// t_node	*convert(t_token *thead)
// {
// 	t_node	*nhead;
// 	char	**args;

// 	nhead = NULL;
// 	while (thead)
// 	{
// 		while (thead)
// 		{
// 			if (thead->type != LXR_WORD)
// 				break ;
// 			args = arypush(args, thead->token);
// 			thead = thead->next;
// 		}
		
// 	}
// }
