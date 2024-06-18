/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yushsato <yushsato@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 04:44:17 by yushsato          #+#    #+#             */
/*   Updated: 2024/06/18 16:05:41 by yushsato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_token	*node_add_input(t_node *target, t_token *cursor);
t_token	*node_add_output(t_node *target, t_token *cursor);
t_token	*node_add_append(t_node *target, t_token *cursor);
t_token	*node_add_redirection(t_node *target, t_token *cursor);
char	**strsallocat(char **ary, char *add);

static void	strs_free(char **strs)
{
	while (strs && *strs)
		free(*strs++);
}

t_node	*node_free(t_node *node)
{
	t_node	*next;

	while (node)
	{
		if (node->args)
			strs_free(node->args);
		if (node->args)
			free(node->args);
		if (node->input_fname)
			free(node->input_fname);
		if (node->hdoc_str)
			free(node->hdoc_str);
		if (node->output_fname)
			free(node->output_fname);
		if (node->append_fname)
			free(node->append_fname);
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
