/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yushsato <yushsato@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 04:17:16 by yushsato          #+#    #+#             */
/*   Updated: 2024/06/21 22:06:34 by yushsato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	sig_exec(int signo);
void	close_pipe(int *pipe);
t_token	*token_last(t_token *head);

t_node	*execute_ready(t_token *cursor)
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
	pid_t	pid;
	int		status;
	int		is_logic;
	
	SIG().set(0);
	node = execute_ready(cursor);
	status = node->cancel;
	if (status && !NODE().free(node))
		return (status);
	head = node;
	pipe(node->lpipe);
	is_logic = 0;
	while (node)
	{
		pipe(node->rpipe);
		if (node->conjection_type == LXR_LOGIC)
		{
			sig_exec(0);
			pid = (EXEC().async)(node, envp);
			close_pipe(node->lpipe);
			status = EXEC().await(pid);
			SIG().shell(0);
			is_logic = status;
		}
		else if (node->conjection_type == LXR_PIPE && !is_logic)
		{
			sig_exec(0);
			pid = (EXEC().async)(node, envp);
			close_pipe(node->lpipe);
			status = EXEC().await(pid);
			SIG().shell(0);
		}
		else if (node->conjection_type == LXR_SCOLON && !is_logic)
		{
			sig_exec(0);
			pid = (EXEC().async)(node, envp);
			close_pipe(node->lpipe);
			status = EXEC().await(pid);
			SIG().shell(0);
			is_logic = 0;
		}
		else if (!is_logic)
		{
			sig_exec(0);
			pid = (EXEC().async)(node, envp);
			close_pipe(node->lpipe);
			status = EXEC().await(pid);
			SIG().shell(0);
		}
		else
			close_pipe(node->lpipe);
		if (node->next)
		{
			ft_memcpy(node->next->lpipe, node->rpipe, sizeof(int) * 2);
			node = node->next;
		}
		else
			break ;
	}
	close_pipe(node->rpipe);
	NODE().free(head);
	return (status);
}
