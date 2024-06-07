/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yushsato <yushsato@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 00:36:42 by yushsato          #+#    #+#             */
/*   Updated: 2024/06/08 00:25:12 by yushsato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_token	*tokenizer(const char *str);

void	lexer_error(t_token token)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(token.token, 2);
	ft_putstr_fd("'\n", 2);
}

t_token	*lexer(const char *input)
{
	t_token	*head;
	t_token	*cursor;
	t_token	*add;

	head = NULL;
	while (*input)
	{
		if (ft_isspace(*input) && input++)
			continue ;
		add = tokenizer(input);
		if (head == NULL && add && ft_memcpy(&head, &add, sizeof(t_token *))
			&& ft_memcpy(&cursor, &add, sizeof(t_token *)))
			input += add->len;
		else if (add && ft_memcpy(&(cursor->next), &add, sizeof(t_token *))
			&& ft_memcpy(&(add->prev), &cursor, sizeof(t_token *))
			&& ft_memcpy(&cursor, &add, sizeof(t_token *)))
			input += cursor->len;
		if (TKN().iserror(cursor))
		{
			lexer_error(*cursor);
			break ;
		}
	}
	return (head);
}
