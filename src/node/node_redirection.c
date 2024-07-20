/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsakanou <nsakanou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 19:44:35 by yushsato          #+#    #+#             */
/*   Updated: 2024/07/16 00:14:25 by nsakanou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#define C cursor
#define T target

char	**strsallocat(char **ary, char *add);
t_token	*node_add_heredoc(t_node *T, t_token *C);
t_token	*token_push(t_token *head, char *token, int len, int type);
t_token	*token_unshift(t_token *head, char *token, int len, int type);

t_token	*node_add_input(t_node *T, t_token *C)
{
	C = C->next;
	T->io_tokens = token_push(T->io_tokens, C->token, C->len, LXR_INPUT);
	return (C->next);
}

t_token	*node_add_output(t_node *T, t_token *C)
{
	C = C->next;
	T->io_tokens = token_push(T->io_tokens, C->token, C->len, LXR_OUTPUT);
	return (C->next);
}

t_token	*node_add_append(t_node *T, t_token *C)
{
	C = C->next;
	T->io_tokens = token_push(T->io_tokens, C->token, C->len, LXR_APPEND);
	return (C->next);
}

t_token	*node_add_redirection(t_node *T, t_token *C)
{
	if (C->type == LXR_INPUT)
		C = node_add_input(T, C);
	else if (C->type == LXR_HEREDOC)
		C = node_add_heredoc(T, C);
	else if (C->type == LXR_OUTPUT)
		C = node_add_output(T, C);
	else if (C->type == LXR_APPEND)
		C = node_add_append(T, C);
	return (C);
}
