/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsakanou <nsakanou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 04:17:16 by yushsato          #+#    #+#             */
/*   Updated: 2024/07/04 13:39:15 by nsakanou         ###   ########.fr       */
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

// int	execute_run(t_token *cursor, char **envp)
// {
// 	t_node	*node;
// 	t_node	*head;
// 	int		ifp[2];
// 	int		ofp[2];
// 	int		is_pipe;
// 	int		is_logic;
// 	int		status;

// 	SIG().set(0);
// 	node = execute_ready(cursor);
// 	head = node;
// 	is_logic = 0;
// 	is_pipe = 0;
// 	status = node->cancel;
// 	if (status && !NODE().free(node))
// 		return (status);
// 	SIG().exec(0);
// 	while (node)
// 	{
// 		ifp[0] = STDIN_FILENO;
// 		ifp[1] = STDOUT_FILENO;
// 		if (is_pipe)
// 			ft_memcpy(ifp, ofp, sizeof(int) * 2);
// 		ofp[0] = STDIN_FILENO;
// 		ofp[1] = STDOUT_FILENO;
// 		if (node->conjection_type == LXR_LOGIC
// 			&& ((is_logic && !status) || !is_logic))
// 		{
// 			EXEC().promise_add((EXEC().async)(node->args, envp, ifp, ofp));
// 			if (is_pipe)
// 				close_pipe(ifp);
// 			is_logic = 1;
// 			is_pipe = 0;
// 		}
// 		else if (node->conjection_type == LXR_PIPE
// 			&& ((is_logic && !status) || !is_logic))
// 		{
// 			pipe(ofp);
// 			EXEC().promise_add((EXEC().async)(node->args, envp, ifp, ofp));
// 			if (is_pipe)
// 				close_pipe(ifp);
// 			is_logic = 0;
// 			is_pipe = 1;
// 		}
// 		else
// 		{
// 			if ((is_logic && !status) || !is_logic)
// 				EXEC().promise_add((EXEC().async)(node->args,envp, ifp, ofp));
// 			if (is_pipe)
// 				close_pipe(ifp);
// 			is_logic = 0;
// 			is_pipe = 0;
// 		}
// 		if (!is_pipe)
// 			status = EXEC().promise_all();
// 		node = node->next;
// 	}
// 	SIG().shell(0);
// 	NODE().free(head);
// 	return (status);
// }

void	handle_logic_node(t_node *node, int *fds, int *status, char **envp)
{
	pid_t	promise;

	if (node->prev == NULL
		|| (node->prev && node->prev->conjection_type == LXR_LOGIC && !*status)
		|| (node->prev && node->prev->conjection_type != LXR_LOGIC))
	{
		promise = (EXEC().async)(node->args, envp, fds, fds + 2);
		EXEC().promise_add(promise);
		if (node->prev && node->prev->conjection_type == LXR_PIPE)
			close_pipe(fds);
	}
}

void	handle_pipe_node(t_node *node, int *fds, int *status, char **envp)
{
	pid_t	promise;

	if ((node->prev && node->prev->conjection_type == LXR_LOGIC && !*status)
		|| (node->prev && node->prev->conjection_type != LXR_LOGIC))
	{
		pipe(fds + 2);
		promise = (EXEC().async)(node->args, envp, fds, fds + 2);
		EXEC().promise_add(promise);
		if (node->prev && node->prev->conjection_type == LXR_PIPE)
			close_pipe(fds);
	}
}

void	handle_other_node(t_node *node, int *fds, int *status, char **envp)
{
	pid_t	promise;

	if ((node->prev && node->prev->conjection_type == LXR_LOGIC && !*status)
		|| (node->prev && node->prev->conjection_type != LXR_LOGIC))
	{
		promise = (EXEC().async)(node->args, envp, fds, fds + 2);
		EXEC().promise_add(promise);
	}
	if (node->prev && node->prev->conjection_type == LXR_PIPE)
		close_pipe(fds);
}

void	process_node(t_node *node, int *status, char **envp)
{
	int	fds[4];

	fds[0] = STDIN_FILENO;
	fds[1] = STDOUT_FILENO;
	if (node->prev && node->prev->conjection_type == LXR_PIPE)
		ft_memcpy(&fds[0], &fds[2], sizeof(int) * 2);
	fds[2] = STDIN_FILENO;
	fds[3] = STDOUT_FILENO;
	if (node->conjection_type == LXR_LOGIC)
		handle_logic_node(node, fds, status, envp);
	else if (node->conjection_type == LXR_PIPE)
		handle_pipe_node(node, fds, status, envp);
	else
		handle_other_node(node, fds, status, envp);
}

int	execute_run(t_token *cursor, char **envp)
{
	t_node	*node;
	t_node	*head;
	int		status;

	SIG().set(0);
	node = execute_ready(cursor);
	head = node;
	status = node->cancel;
	if (status && !NODE().free(node))
		return (status);
	SIG().exec(0);
	while (node)
	{
		process_node(node, &status, envp);
		if (!(node->prev && node->prev->conjection_type == LXR_PIPE))
			status = EXEC().promise_all();
		node = node->next;
	}
	SIG().shell(0);
	NODE().free(head);
	return (status);
}
