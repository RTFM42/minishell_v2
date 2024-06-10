/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sanitize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yushsato <yushsato@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 15:42:35 by yushsato          #+#    #+#             */
/*   Updated: 2024/06/10 16:44:22 by yushsato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_token	*sanitize_token(t_token *head)
{
	t_token	*courser;

	courser = head;
	while (courser)
	{
		courser->len = ft_strlen(courser->token);
		courser = courser->next;
	}
	return (head);
}
