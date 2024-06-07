/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yushsato <yushsato@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 17:30:44 by yushsato          #+#    #+#             */
/*   Updated: 2024/06/07 17:01:48 by yushsato         ###   ########.fr       */
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
	while (token)
	{
		if (token->type == LXR_ERROR)
			return (1);
		token = token->next;
	}
	return (0);
}

t_tokenc	token_constructor(void)
{
	static const t_tokenc	tokenc = {
		.new = token_new,
		.iserror = token_iserror,
	};

	return (tokenc);
}
