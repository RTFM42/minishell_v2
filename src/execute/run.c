/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yushsato <yushsato@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 04:17:16 by yushsato          #+#    #+#             */
/*   Updated: 2024/07/20 00:38:21 by yushsato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	close_pipe(int *pipe);
int		isbuiltin(const char *fname);
int		exec_builtin(char *const *argv, char *const *envp, int *ofd);
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

static int	execute_iofd(t_token *io, int *ifd, int *ofd, char **dhd)
{
	int		fd;

	*dhd = NULL;
	ERR().setno(0);
	while (io)
	{
		if (!*dhd)
			free(*dhd);
		*dhd = NULL;
		if ((io->type == LXR_HEREDOC || io->type == LXR_INPUT) && ifd[0] == 0
			&& pipe(ifd) == -1 && ERR().print("pipe"))
			return (-1);
		if ((io->type == LXR_OUTPUT || io->type == LXR_APPEND) && ofd[1] == 1
			&& pipe(ofd) == -1 && ERR().print("pipe"))
			return (-1);
		if (io->type == LXR_HEREDOC)
			*dhd = ft_strdup(io->token);
		else if (io->type == LXR_INPUT)
		{
			fd = sf_fopen(io->token, O_RDONLY);
			if (fd != -1 && dup2(fd, ifd[0]) != -1)
				sf_close(fd);
			else if (ERR().print(io->token))
				return (-1);
		}
		else if (io->type == LXR_OUTPUT)
		{
			fd = open(io->token, O_CREAT | O_RDWR | O_TRUNC, 0644);
			if (fd != -1 && dup2(fd, ofd[1]) != -1)
				sf_close(fd);
			else if(ERR().print(io->token))
				return (-1);
		}
		else if (io->type == LXR_APPEND)
		{
			fd = open(io->token, O_CREAT | O_RDWR | O_APPEND, 0644);
			if (fd != -1 && dup2(fd, ofd[1]) != -1)
				sf_close(fd);
			else if (ERR().print(io->token))
				return (-1);
		}
		io = io->next;
	}
	return (0);
}

int	execute_run(t_token *cursor, char **envp)
{
	t_node	*node;
	t_node	*head;
	int		ifp[2];
	int		ofp[2];
	int		ifd[2];
	int		ofd[2];
	char	*heredoc;
	int		is_pipe;
	int		is_logic;
	int		is_promise;
	int		status;
	int		fd_stat;

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
		status = 0;
		fd_stat = 0;
		is_promise = 0;
		ifp[0] = STDIN_FILENO;
		ifp[1] = STDOUT_FILENO;
		if (is_pipe)
			ft_memcpy(ifp, ofp, sizeof(int) * 2);
		ofp[0] = STDIN_FILENO;
		ofp[1] = STDOUT_FILENO;
		ft_memcpy(ifd, ofp, sizeof(int) * 2);
		ft_memcpy(ofd, ofp, sizeof(int) * 2);
		heredoc = NULL;
		ERR().setno(0);
		if (node->io_tokens)
			fd_stat = execute_iofd(node->io_tokens, ifd, ofd, &heredoc);
		status = fd_stat * -1;
		if (node->conjection_type == LXR_LOGIC
			&& ((is_logic && !status) || !is_logic))
		{
			if (ifd[0] == 0)
				ft_memcpy(ifd, ifp, sizeof(int) * 2);
			if (ofd[1] == 1)
				ft_memcpy(ofd, ofp, sizeof(int) * 2);
			if (!fd_stat && !is_pipe && isbuiltin(node->args[0]))
				status = exec_builtin(node->args, envp, ofd);
			else if (!fd_stat)
			{
				is_promise = 1;
				EXEC().promise_add((EXEC().async)(node->args, envp, ifd, ofd));
				if (g_signal != 0)
					status = g_signal;
				if (heredoc != NULL)
				{
					write(ifd[1], heredoc, ft_strlen(heredoc));
					free(heredoc);
				}
			}
			if (is_pipe)
				close_pipe(ifp);
			is_logic = 1;
			is_pipe = 0;
		}
		else if (node->conjection_type == LXR_PIPE
			&& ((is_logic && !status) || !is_logic))
		{
			pipe(ofp);
			if (ifd[0] == 0)
				ft_memcpy(ifd, ifp, sizeof(int) * 2);
			if (ofd[1] == 1)
				ft_memcpy(ofd, ofp, sizeof(int) * 2);
			if (!fd_stat)
			{
				is_promise = 1;
				EXEC().promise_add((EXEC().async)(node->args, envp, ifd, ofd));
				if (g_signal != 0)
					status = g_signal;
			}
			if (heredoc)
			{
				write(ifd[1], heredoc, ft_strlen(heredoc));
				free(heredoc);
			}
			if (is_pipe)
				close_pipe(ifp);
			is_logic = 0;
			is_pipe = 1;
		}
		else
		{
			if (ifd[0] == 0)
				ft_memcpy(ifd, ifp, sizeof(int) * 2);
			if (ofd[1] == 1)
				ft_memcpy(ofd, ofp, sizeof(int) * 2);
			if ((is_logic && !status) || !is_logic)
			{
				if (!fd_stat && !is_pipe && isbuiltin(node->args[0]))
					status = exec_builtin(node->args, envp, ofd);
				else if (!fd_stat)
				{
					is_promise = 1;
					EXEC().promise_add((EXEC().async)(node->args, envp, ifd, ofd));
					if (g_signal != 0)
						status = g_signal;
					if (heredoc)
					{
						write(ifd[1], heredoc, ft_strlen(heredoc));
						free(heredoc);
					}
				}
			}
			if (is_pipe)
				close_pipe(ifp);
			is_logic = 0;
			is_pipe = 0;
		}
		if (ifd[0] != 0 && ifd[0] != ifp[0])
			close_pipe(ifd);
		if (ofd[1] != 0 && ofd[1] != ofp[1])
			close_pipe(ofd);
		if (!is_pipe && is_promise)
		{
			if (!status)
				status = EXEC().promise_all();
			else
				EXEC().promise_all();
		}
		node = node->next;
	}
	SIG().shell(0);
	NODE().free(head);
	return (status);
}
