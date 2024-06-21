/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   async.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yushsato <yushsato@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 01:12:08 by yushsato          #+#    #+#             */
/*   Updated: 2024/06/21 22:14:11 by yushsato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	shell_io(t_node *node)
{
	t_token	*in;
	t_token	*out;
	int		infd;
	int		outfd;

	in = node->in_tokens;
	if (node->prev && node->prev->conjection_type == LXR_PIPE && in == NULL)
	{
		if (!node->prev->out_tokens)
			dup2(node->lpipe[0], STDIN_FILENO);
	}
	while (in)
	{
		if (in->type == LXR_INPUT)
		{
			infd = open(in->token, O_RDONLY);
			if (infd < 0)
				(ERR().exit)(in->token, 1);
			if (in->next == NULL)
				dup2(infd, STDIN_FILENO);
		}
		else if (in->type == LXR_HEREDOC)
		{
			if (in->next == NULL)
			{
				dup2(node->lpipe[0], STDIN_FILENO);
				write(node->lpipe[1], in->token, in->len);
				close(node->lpipe[0]);
			}
		}
		in = in->next;
	}
	close(node->lpipe[1]);
	out = node->out_tokens;
	if (node->next != NULL && node->conjection_type == LXR_PIPE && out == NULL)
	{
		dup2(node->rpipe[1], STDOUT_FILENO);
	}
	while (out)
	{
		if (out->type == LXR_OUTPUT)
		{
			outfd = open(out->token, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (outfd < 0)
				(ERR().exit)(out->token, 1);
			if (out->next == NULL)
				dup2(outfd, STDOUT_FILENO);
		}
		else if (out->type == LXR_APPEND)
		{
			outfd = open(out->token, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (outfd < 0)
				(ERR().exit)(out->token, 1);
			if (out->next == NULL)
				dup2(outfd, STDOUT_FILENO);
		}
		out = out->next;
	}
}

pid_t	execute_async(t_node *node, char *const *envp)
{
	char	*path;
	pid_t	pid;

	path = PATH().resolve(node->args[0]);
	pid = fork();
	if (pid == 0)
	{
		shell_io(node);
		execve(path, node->args, envp);
		(ERR().exit)(node->args[0], 1);
	}
	if (pid == -1)
		ERR().print(node->args[0]);
	free(path);
	return (pid);
}
