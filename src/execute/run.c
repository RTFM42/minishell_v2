/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yushsato <yushsato@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 04:17:16 by yushsato          #+#    #+#             */
/*   Updated: 2024/07/21 02:11:57 by yushsato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	close_pipe(int *pipe);
int		isbuiltin(const char *fname);
int		exec_builtin(char *const *argv, char *const *envp, int *ofd);
int		exec_iofd(t_token *io, int *ifd, int *ofd, char **dhd);
t_token	*token_last(t_token *head);

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

static void	elogic(t_exec *exec, char **envp)
{
	if (exec->ifd[0] == 0)
		ft_memcpy(exec->ifd, exec->ifp, sizeof(int) * 2);
	if (exec->ofd[1] == 1)
		ft_memcpy(exec->ofd, exec->ofp, sizeof(int) * 2);
	if (!exec->fd_stat && !exec->is_pipe && isbuiltin(exec->node->args[0]))
		exec->status = exec_builtin(exec->node->args, envp, exec->ofd);
	else if (!exec->fd_stat)
	{
		exec->is_promise = 1;
		EXEC().promise_add((EXEC().async)(exec->node->args,
			envp, exec->ifd, exec->ofd));
		if (g_signal != 0)
			exec->status = g_signal;
		if (exec->heredoc != NULL)
		{
			write(exec->ifd[1], exec->heredoc, ft_strlen(exec->heredoc));
			free(exec->heredoc);
		}
	}
	if (exec->is_pipe)
		close_pipe(exec->ifp);
	exec->is_logic = 1;
	exec->is_pipe = 0;
}

static void	epipe(t_exec *exec, char **envp)
{
	pipe(exec->ofp);
	if (exec->ifd[0] == 0)
		ft_memcpy(exec->ifd, exec->ifp, sizeof(int) * 2);
	if (exec->ofd[1] == 1)
		ft_memcpy(exec->ofd, exec->ofp, sizeof(int) * 2);
	if (!exec->fd_stat)
	{
		exec->is_promise = 1;
		EXEC().promise_add((EXEC().async)(exec->node->args,
			envp, exec->ifd, exec->ofd));
		if (g_signal != 0)
			exec->status = g_signal;
	}
	if (exec->heredoc)
	{
		write(exec->ifd[1], exec->heredoc, ft_strlen(exec->heredoc));
		free(exec->heredoc);
	}
	if (exec->is_pipe)
		close_pipe(exec->ifp);
	exec->is_logic = 0;
	exec->is_pipe = 1;
}

static void	enormal(t_exec *exec, char **envp)
{
	if (exec->ifd[0] == 0)
		ft_memcpy(exec->ifd, exec->ifp, sizeof(int) * 2);
	if (exec->ofd[1] == 1)
		ft_memcpy(exec->ofd, exec->ofp, sizeof(int) * 2);
	if ((exec->is_logic && !exec->status) || !exec->is_logic)
	{
		if (!exec->fd_stat && !exec->is_pipe && isbuiltin(exec->node->args[0]))
			exec->status = exec_builtin(exec->node->args, envp, exec->ofd);
		else if (!exec->fd_stat)
		{
			exec->is_promise = 1;
			EXEC().promise_add((EXEC().async)(exec->node->args,
				envp, exec->ifd, exec->ofd));
			if (g_signal != 0)
				exec->status = g_signal;
			if (exec->heredoc && write(exec->ifd[1],
					exec->heredoc, ft_strlen(exec->heredoc)))
				free(exec->heredoc);
		}
	}
	if (exec->is_pipe)
		close_pipe(exec->ifp);
	exec->is_logic = 0;
	exec->is_pipe = 0;
}

static void	eawait(t_exec *exec)
{
	if (exec->ifd[0] != 0 && exec->ifd[0] != exec->ifp[0])
		close_pipe(exec->ifd);
	if (exec->ofd[1] != 0 && exec->ofd[1] != exec->ofp[1])
		close_pipe(exec->ofd);
	if (!exec->is_pipe && exec->is_promise)
	{
		if (!exec->status)
			exec->status = EXEC().promise_all();
		else
			EXEC().promise_all();
	}
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
			elogic(&exec, envp);
		else if (exec.node->conjection_type == LXR_PIPE
			&& ((exec.is_logic && !exec.status) || !exec.is_logic))
			epipe(&exec, envp);
		else
			enormal(&exec, envp);
		eawait(&exec);
		exec.node = exec.node->next;
	}
	SIG().shell(0);
	NODE().free(exec.head);
	return (exec.status);
}
