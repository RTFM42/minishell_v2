/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sanitizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yushsato <yushsato@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 15:42:35 by yushsato          #+#    #+#             */
/*   Updated: 2024/06/17 00:15:01 by yushsato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#define C cursor

int	error(t_token token);

t_token	*sanitizer(t_token *head)
{
	t_token	*cursor;

	cursor = head;
	while (cursor)
	{
		cursor->len = ft_strlen(cursor->token);
		if ((C->next == NULL && LXR_INPUT <= C->type && C->type <= LXR_LOGIC
				&& error(*cursor)) || (C->type == LXR_ERROR && error(*cursor)))
		{
			cursor->type = LXR_ERROR;
			break ;
		}
		cursor = cursor->next;
	}
	return (head);
}
