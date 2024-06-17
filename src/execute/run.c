/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yushsato <yushsato@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 04:17:16 by yushsato          #+#    #+#             */
/*   Updated: 2024/06/17 20:36:35 by yushsato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/** WIP
 * node_print - For debugging, print the node structure
 */
void	node_print(t_node *node)
{
	char	**args;
	ft_printf(
		"{\n"
		"\t\"last_output_type\": %d,\n"
		"\t\"last_input_type\": %d,\n"
		"\t\"conjection_type\": %d,\n"
		"\t\"exit_status\": %d,\n"
		"\t\"args\": [",
		node->last_output_type, node->last_input_type, node->conjection_type,
		node->exit_status
	);
	args = node->args;
	while (*args)
	{
		ft_printf("\"%s\"", *args);
		args++;
		if (*args)
			ft_printf(", ");
	}
	ft_printf(
		"],\n"
		"\t\"input_fname\": %s,\n"
		"\t\"hdoc_str\": %s,\n"
		"\t\"output_fname\": %s,\n"
		"\t\"append_fname\": %s\n"
		"}\n",
		node->input_fname, node->hdoc_str, node->output_fname,
		node->append_fname
	);
}

t_node	*execute_ready(t_token *cursor)
{
	t_node	*head;
	t_node	*node;

	node = ft_calloc(1, sizeof(t_node));
	head = node;
	while (cursor)
	{
		if (LXR_PIPE <= cursor->type)
		{
			node->conjection_type = cursor->type;
			if (cursor->next)
			{
				node->next = NODE().new(node);
				node->next->prev = node;
				node = node->next;
			}
		}
		if (LXR_INPUT <= cursor->type)
			cursor = NODE().add_redir(node, cursor);
		else
			cursor = NODE().add_args(node, cursor);
	}
	return (head);
}

void	inputer(char *fname, int infd)
{
	ssize_t	bytes;
	char	buffer[1024];
	int		openfd;

	bytes = 1;
	openfd = open(fname, O_RDONLY);
	while (1)
	{
		bytes = read(openfd, buffer, sizeof(buffer));
		if (bytes == 0)
			break ;
		write(infd, buffer, bytes);
	}
	sf_close(openfd);
}

void	heredoc(int infd, char *hdoc_str)
{
	if (hdoc_str)
		write(infd, hdoc_str, ft_strlen(hdoc_str));
	write(infd, "\0", 1);
}

void	outputer(int outfd, char *fname)
{
	ssize_t	bytes;
	char	buffer[1024];
	int		openfd;

	bytes = 1;
	openfd = open(fname, O_WRONLY);
	while (1)
	{
		bytes = read(outfd, buffer, sizeof(buffer));
		if (bytes == 0)
			break ;
		write(openfd, buffer, bytes);
	}
	sf_close(openfd);
}

void	appender(int outfd, char *fname)
{
	ssize_t	bytes;
	char	buffer[1024];
	int		openfd;

	bytes = 1;
	openfd = open(fname, O_APPEND);
	while (1)
	{
		bytes = read(outfd, buffer, sizeof(buffer));
		if (bytes == 0)
			break ;
		write(openfd, buffer, bytes);
	}
	sf_close(openfd);
}

int	execute_scolon(t_node *node, char **envp, int *lp, int *rp)
{
	int		clp[2];
	int		crp[2];
	pid_t	pid;

	ft_memcpy(clp, lp, sizeof(int) * 2);
	ft_memcpy(crp, rp, sizeof(int) * 2);
	if (node->last_input_type == 0)
		clp[0] = STDIN_FILENO;
	if (node->last_output_type == 0)
		crp[1] = STDOUT_FILENO;
	pid = EXEC().async(node->args, envp, clp, crp);
	sf_close(lp[0]);
	if (node->last_input_type == LXR_INPUT)
		inputer(node->input_fname, clp[1]);
	else if (node->last_input_type == LXR_HEREDOC)
		heredoc(clp[1], node->hdoc_str);
	if (node->last_input_type == LXR_OUTPUT)
		outputer(crp[0], node->output_fname);
	else if (node->last_input_type == LXR_APPEND)
		appender(crp[0], node->append_fname);
	sf_close(lp[1]);
	node->exit_status = EXEC().await(pid);
	return (node->exit_status);
}

int	execute_run(t_token *cursor, char **envp)
{
	t_node	*node;
	t_node	*head;
	int		lp[2];
	int		rp[2];
	
	node = execute_ready(cursor);
	head = node;
	while (node)
	{
		node_print(node);
		pipe(lp);
		pipe(rp);
		if (node->conjection_type == LXR_SCOLON || node->conjection_type == 0)
			execute_scolon(node, envp, lp, rp);
		else
		{
			sf_close(lp[0]);
			sf_close(lp[1]);
		}
		node = node->next;
		lp[0] = rp[0];
		lp[1] = rp[1];
	}
	sf_close(rp[0]);
	sf_close(rp[1]);
	NODE().free(head);
	return (0);
}
