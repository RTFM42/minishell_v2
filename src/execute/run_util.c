/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yushsato <yushsato@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 02:13:21 by yushsato          #+#    #+#             */
/*   Updated: 2024/07/21 02:32:10 by yushsato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	close_pipe(int *pipe);
int		isbuiltin(const char *fname);
int		exec_builtin(char *const *argv, char *const *envp, int *ofd);
pid_t	async(char *const *argv, char *const *envp, int *ifp, int *ofp);
void	promise_add(pid_t pid);

void	exec_logic(t_exec *exec, char **envp)
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
		promise_add(async(exec->node->args, envp, exec->ifd, exec->ofd));
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

void	exec_pipe(t_exec *exec, char **envp)
{
	pipe(exec->ofp);
	if (exec->ifd[0] == 0)
		ft_memcpy(exec->ifd, exec->ifp, sizeof(int) * 2);
	if (exec->ofd[1] == 1)
		ft_memcpy(exec->ofd, exec->ofp, sizeof(int) * 2);
	if (!exec->fd_stat)
	{
		exec->is_promise = 1;
		promise_add(async(exec->node->args, envp, exec->ifd, exec->ofd));
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

void	exec_normal(t_exec *exec, char **envp)
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
			promise_add(async(exec->node->args, envp, exec->ifd, exec->ofd));
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

void	exec_await(t_exec *exec)
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
