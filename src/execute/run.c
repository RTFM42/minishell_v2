/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yushsato <yushsato@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 04:17:16 by yushsato          #+#    #+#             */
/*   Updated: 2024/06/18 18:55:44 by yushsato         ###   ########.fr       */
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
		if (*++args)
			ft_printf(", ");
	}
	ft_printf(
		"],\n"
		"\t\"input_fname\": %s,\n"
		"\t\"hdoc_str\": %s,\n"
		"\t\"output_fname\": %s,\n"
		"\t\"append_fname\": %s\n"
		"}\n",
		node->input_fname,
		node->hdoc_str,
		node->output_fname,
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
			if (node->cancel && ++(head->cancel))
				break ;
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

int	execute_scolon(t_node *node, char **envp, int *lp, int *rp)
{
	t_io	li;
	t_io	ri;
	pid_t	pid;

	ft_memcpy(li.pipe, lp, sizeof(int) * 2);
	ft_memcpy(ri.pipe, rp, sizeof(int) * 2);
	if (node->last_input_type == LXR_INPUT)
		li.info = node->input_fname;
	li.type = node->last_input_type;
	if (node->last_output_type == LXR_OUTPUT)
		ri.info = node->output_fname;
	if (node->last_output_type == LXR_APPEND)
		ri.info = node->append_fname;
	ri.type = node->last_output_type;
	pid = (EXEC().async)(node->args, envp, li, ri);
	if (node->last_input_type == LXR_HEREDOC)
		write(lp[1], node->hdoc_str, ft_strlen(node->hdoc_str));
	sf_close(lp[0]);
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
	if (node->cancel)
	{
		NODE().free(node);
		return (1);
	}
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
