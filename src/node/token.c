/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yushsato <yushsato@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 13:24:42 by yushsato          #+#    #+#             */
/*   Updated: 2024/07/02 17:01:23 by yushsato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#define C cursor
#define T target

t_token	*token_push(t_token *head, char *token, int len, int type)
{
	t_token	*cursor;

	if (head == NULL)
		return (TKN().new(ft_strdup(token), len, type));
	C = head;
	while (C && C->next)
		C = C->next;
	C->next = TKN().new(ft_strdup(token), len, type);
	C->next->prev = C;
	return (head);
}

t_token	*token_unshift(t_token *head, char *token, int len, int type)
{
	t_token	*cursor;

	if (head == NULL)
		return (TKN().new(ft_strdup(token), len, type));
	C = TKN().new(ft_strdup(token), len, type);
	C->next = head;
	head->prev = C;
	return (C);
}

t_token	*token_last(t_token *head)
{
	t_token	*cursor;

	C = head;
	while (C && C->next)
		C = C->next;
	return (C);
}
