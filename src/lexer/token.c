/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yushsato <yushsato@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 17:30:44 by yushsato          #+#    #+#             */
/*   Updated: 2024/06/22 15:16:54 by yushsato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_token	*token_new(char *token, int len, int type)
{
	t_token	*new;

	new = ft_calloc(1, sizeof(t_token));
	new->token = token;
	new->len = len;
	new->type = type;
	return (new);
}

int	token_iserror(t_token *token)
{
	if (token && token->type == LXR_ERROR)
		return (1);
	return (0);
}

void	token_freeall(t_token *head)
{
	t_token	*next;

	if (!head)
		return ;
	while (head)
	{
		next = head->next;
		free(head->token);
		free(head);
		head = next;
	}
}

t_tokenc	token_constructor(void)
{
	static const t_tokenc	tokenc = {
		.new = token_new,
		.iserror = token_iserror,
		.freeall = token_freeall
	};

	return (tokenc);
}
