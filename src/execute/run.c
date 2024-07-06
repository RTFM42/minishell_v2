/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yushsato <yushsato@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 04:17:16 by yushsato          #+#    #+#             */
/*   Updated: 2024/07/06 13:55:14 by yushsato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	close_pipe(int *pipe);
t_token	*token_last(t_token *head);

static t_node	*execute_ready(t_token *cursor)
{
	t_node	*head;
	t_node	*node;

	node = NODE().new(NULL);
	head = node;
	while (cursor)
	{
		if (LXR_PIPE <= cursor->type)
		{
			node->conjection_type = cursor->type;
			head->cancel = node->cancel;
			if (node->cancel || !cursor->next)
				break ;
			node->next = NODE().new(node);
			node->next->prev = node;
			node = node->next;
			cursor = cursor->next;
		}
		if (LXR_INPUT <= cursor->type)
			cursor = NODE().add_redir(node, cursor);
		else
			cursor = NODE().add_args(node, cursor);
	}
	return (head);
}

int	execute_run(t_token *cursor, char **envp)
{
	t_node	*node;
	t_node	*head;
	int		ifp[2];
	int		ofp[2];
	int		is_pipe;
	int		is_logic;
	int		status;

	SIG().set(0);
	node = execute_ready(cursor);
	head = node;
	is_logic = 0;
	is_pipe = 0;
	status = node->cancel;
	if (status && !NODE().free(node))
		return (status);
	SIG().exec(0);
	while (node)
	{
		ifp[0] = STDIN_FILENO;
		ifp[1] = STDOUT_FILENO;
		if (is_pipe)
			ft_memcpy(ifp, ofp, sizeof(int) * 2);
		ofp[0] = STDIN_FILENO;
		ofp[1] = STDOUT_FILENO;
		if (node->conjection_type == LXR_LOGIC
			&& ((is_logic && !status) || !is_logic))
		{
			EXEC().promise_add((EXEC().async)(node->args, envp, ifp, ofp));
			if (is_pipe)
				close_pipe(ifp);
			is_logic = 1;
			is_pipe = 0;
		}
		else if (node->conjection_type == LXR_PIPE
			&& ((is_logic && !status) || !is_logic))
		{
			pipe(ofp);
			EXEC().promise_add((EXEC().async)(node->args, envp, ifp, ofp));
			if (is_pipe)
				close_pipe(ifp);
			is_logic = 0;
			is_pipe = 1;
		}
		else
		{
			if ((is_logic && !status) || !is_logic)
				EXEC().promise_add((EXEC().async)(node->args,envp, ifp, ofp));
			if (is_pipe)
				close_pipe(ifp);
			is_logic = 0;
			is_pipe = 0;
		}
		if (!is_pipe)
			status = EXEC().promise_all();
		node = node->next;
	}
	SIG().shell(0);
	NODE().free(head);
	return (status);
}
