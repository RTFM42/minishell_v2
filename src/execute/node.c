/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yushsato <yushsato@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 04:44:17 by yushsato          #+#    #+#             */
/*   Updated: 2024/06/20 13:23:45 by yushsato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_token	*node_add_input(t_node *target, t_token *cursor);
t_token	*node_add_output(t_node *target, t_token *cursor);
t_token	*node_add_append(t_node *target, t_token *cursor);
t_token	*node_add_redirection(t_node *target, t_token *cursor);
char	**strsallocat(char **ary, char *add);

static int	strs_free(char **strs)
{
	while (strs && *strs)
		free(*strs++);
	return (1);
}

t_node	*node_free(t_node *node)
{
	t_node	*next;

	while (node)
	{
		if (node->lpipe)
			free(node->lpipe);
		if (node->rpipe)
			free(node->rpipe);
		if (node->args && strs_free(node->args))
			free(node->args);
		TKN().freeall(node->in_tokens);
		TKN().freeall(node->out_tokens);
		next = node->next;
		free(node);
		node = next;
	}
	return (NULL);
}

t_node	*node_new(t_node *prev)
{
	t_node	*node;

	node = ft_calloc(1, sizeof(t_node));
	node->lpipe = ft_calloc(3, sizeof(int));
	node->rpipe = ft_calloc(3, sizeof(int));
	if (prev)
	{
		node->prev = prev;
		prev->next = node;
	}
	return (node);
}

t_token	*node_add_args(t_node *target, t_token *cursor)
{
	target->args = strsallocat(target->args, cursor->token);
	return (cursor->next);
}

t_nodec	node_constructor(void)
{
	static const t_nodec	node = {
		.free = node_free,
		.new = node_new,
		.add_args = node_add_args,
		.add_redir = node_add_redirection,
	};

	return (node);
}
