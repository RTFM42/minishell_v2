/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yushsato <yushsato@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 17:30:44 by yushsato          #+#    #+#             */
/*   Updated: 2024/06/08 00:03:22 by yushsato         ###   ########.fr       */
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

void	token_printall(t_token *head)
{
	while (head)
	{
		if (head->type == LXR_WORD)
			ft_printf("token[%d](%s): %s", head->len, head->token,"WORD");
		else if (head->type == LXR_PIPE)
			ft_printf("token[%d](%s): %s", head->len, head->token,"PIPE");
		else if (head->type == LXR_INPUT)
			ft_printf("token[%d](%s): %s", head->len, head->token,"OUTPUT");
		else if (head->type == LXR_HEREDOC)
			ft_printf("token[%d](%s): %s", head->len, head->token,"HEREDOC");
		else if (head->type == LXR_APPEND)
			ft_printf("token[%d](%s): %s", head->len, head->token,"APPEND");
		else if (head->type == LXR_LOGIC)
			ft_printf("token[%d](%s): %s", head->len, head->token,"LOGIC");
		else if (head->type == LXR_ERROR)
			ft_printf("token[%d](%s): %s", head->len, head->token,"ERROR");
		else
			ft_printf("token[%d](%s): %s", head->len, head->token,"unhandled type");
		head = head->next;
	}
}

t_tokenc	token_constructor(void)
{
	static const t_tokenc	tokenc = {
		.new = token_new,
		.iserror = token_iserror,
		.freeall = token_freeall,
		.printall = token_printall,
	};

	return (tokenc);
}
