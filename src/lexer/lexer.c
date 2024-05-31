/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yushsato <yushsato@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 00:36:42 by yushsato          #+#    #+#             */
/*   Updated: 2024/05/31 01:11:24 by yushsato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_token	*lexer(char *input)
{
	t_token	*head;
	t_token	*cursor;
	t_token	*add;
	
	head = NULL;
	while (*input)
	{
		if (ft_isspace(*input) && input++)
			continue ;
		add = token(*input);
		if (head == NULL)
		{
			head = add;
			cursor = add;
		}
		else
		{
			cursor->next = add;
			add->prev = cursor;
		}
		input++;
	}
	return (head);
}
