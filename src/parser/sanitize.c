/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sanitize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yushsato <yushsato@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 15:42:35 by yushsato          #+#    #+#             */
/*   Updated: 2024/06/16 23:19:52 by yushsato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_token	*sanitize_token(t_token *head)
{
	t_token	*cursor;

	cursor = head;
	while (cursor)
	{
		cursor->len = ft_strlen(cursor->token);
		if (cursor->next == NULL
			&& LXR_INPUT <= cursor->type && LXR_SCOLON != cursor->type)
			cursor->type = LXR_ERROR;
		cursor = cursor->next;
	}
	return (head);
}
