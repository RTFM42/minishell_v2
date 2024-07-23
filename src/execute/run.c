/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yushsato <yushsato@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 04:17:16 by yushsato          #+#    #+#             */
/*   Updated: 2024/07/23 17:21:28 by yushsato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdlib.h>

int		exec_iofd(t_token *io, int *ifd, int *ofd, char **dhd);
void	exec_logic(t_exec *exec, char **envp);
void	exec_pipe(t_exec *exec, char **envp);
void	exec_normal(t_exec *exec, char **envp);
void	exec_await(t_exec *exec);

static t_node	*ready(t_token *cursor)
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

static int	init(t_exec *exec, t_token *cursor)
{
	SIG().set(0);
	exec->node = ready(cursor);
	exec->head = exec->node;
	exec->is_logic = 0;
	exec->is_pipe = 0;
	exec->status = exec->node->cancel;
	if (exec->status)
	{
		NODE().free(exec->node);
		return (exec->status);
	}
	SIG().exec(0);
	return (0);
}

static int	reset(t_exec *exec)
{
	exec->status = 0;
	exec->fd_stat = 0;
	exec->is_promise = 0;
	exec->ifp[0] = STDIN_FILENO;
	exec->ifp[1] = STDOUT_FILENO;
	if (exec->is_pipe)
		ft_memcpy(exec->ifp, exec->ofp, sizeof(int) * 2);
	exec->ofp[0] = STDIN_FILENO;
	exec->ofp[1] = STDOUT_FILENO;
	ft_memcpy(exec->ifd, exec->ofp, sizeof(int) * 2);
	ft_memcpy(exec->ofd, exec->ofp, sizeof(int) * 2);
	exec->heredoc = NULL;
	ERR().setno(0);
	if (exec->node->io_tokens)
		exec->fd_stat = exec_iofd(exec->node->io_tokens,
				exec->ifd, exec->ofd, &(exec->heredoc));
	exec->status = exec->fd_stat * -1;
	return (1);
}

int	execute_run(t_token *cursor, char **envp)
{
	t_exec	exec;

	if (init(&exec, cursor))
		return (exec.status);
	while (exec.node && reset(&exec))
	{
		if (exec.node->conjection_type == LXR_LOGIC
			&& ((exec.is_logic && !exec.status) || !exec.is_logic))
			exec_logic(&exec, envp);
		else if (exec.node->conjection_type == LXR_PIPE
			&& ((exec.is_logic && !exec.status) || !exec.is_logic))
			exec_pipe(&exec, envp);
		else
			exec_normal(&exec, envp);
		exec_await(&exec);
		exec.node = exec.node->next;
	}
	SIG().shell(0);
	NODE().free(exec.head);
	return (exec.status);
}
