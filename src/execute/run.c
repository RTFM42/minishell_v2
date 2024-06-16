/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yushsato <yushsato@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 04:17:16 by yushsato          #+#    #+#             */
/*   Updated: 2024/06/17 01:07:07 by yushsato         ###   ########.fr       */
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
		"{"
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

int	execute_run(t_token *cursor, char **envp)
{
	t_node	*node;
	t_node	*head;
	// int		lp[2];
	// int		rp[2];
	
	node = execute_ready(cursor);
	head = node;
	(void)envp;
	ft_printf("execute_run\n");
	while (node)
	{
		node_print(node);
		node = node->next;
	}
	// while (node)
	// {
	// 	pipe(lp);
	// 	pipe(rp);
	// 	if (node->conjection_type == LXR_SCOLON)
	// 	{
	// 		EXEC().pipe(node->args, envp, lp[1], rp[0]);
	// 		if (lp)
	// 		{
	// 			node->
	// 		}
	// 		close(lp[0]);
	// 		close(lp[1]);
	// 		lp[0] = rp[0];
	// 		lp[1] = rp[1];
	// 	}
	// }
	NODE().free(head);
	return (0);
}
