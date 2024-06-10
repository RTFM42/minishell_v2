/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sanitize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yushsato <yushsato@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 15:42:35 by yushsato          #+#    #+#             */
/*   Updated: 2024/06/10 16:40:02 by yushsato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_token	*sanitize_token(t_token *head)
{
	t_token	*courser;
	t_token	*tmp;

	courser = head;
	while (courser)
	{
		if (courser->token == NULL || courser->token[0] == '\0')
		{
			tmp = courser->next;
			if (courser->prev)
				courser->prev->next = courser->next;
			else
				head = courser->next;
			if (courser->next)
				courser->next->prev = courser->prev;
			free(courser->token);
			free(courser);
			courser = tmp;
			continue ;
		}
		courser->len = ft_strlen(courser->token);
		courser = courser->next;
	}
	return (head);
}
