/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yushsato <yushsato@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 19:44:35 by yushsato          #+#    #+#             */
/*   Updated: 2024/06/16 16:24:12 by yushsato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*strallocat(char *dst, const char *add, int len);

t_token	*node_add_input(t_node *target, t_token *cursor)
{
	cursor = cursor->next;
	if (target->input_fname)
		free(target->input_fname);
	target->input_fname = ft_strdup(cursor->token);
	target->last_input_type = LXR_INPUT;
	cursor = cursor->next;
	return (cursor);
}

t_token	*node_add_heredoc(t_node *target, t_token *cursor)
{
	char	*line;

	line = NULL;
	cursor = cursor->next;
	SIG().herdoc(0);
	if (target->heredoc_str)
	{
		free(target->heredoc_str);
		target->heredoc_str = NULL;
	}
	while (ft_memcmp(line, cursor->token, cursor->len)
		&& line[cursor->len] != '\0')
	{
		line = readline("> ");
		if (line)
		{
			target->heredoc_str = strallocat(target->heredoc_str,
					line, ft_strlen(line));
			free(line);
		}
	}
	SIG().shell(0);
	target->last_input_type = LXR_HEREDOC;
	cursor = cursor->next;
	return (cursor);
}

t_token	*node_add_output(t_node *target, t_token *cursor)
{
	cursor = cursor->next;
	if (target->output_fname)
		free(target->output_fname);
	target->output_fname = ft_strdup(cursor->token);
	target->last_output_type = LXR_OUTPUT;
	cursor = cursor->next;
	return (cursor);
}

t_token	*node_add_append(t_node *target, t_token *cursor)
{
	cursor = cursor->next;
	if (target->append_fname)
		free(target->append_fname);
	target->append_fname = ft_strdup(cursor->token);
	target->last_output_type = LXR_APPEND;
	cursor = cursor->next;
	return (cursor);
}

t_token	*node_add_redirection(t_node *target, t_token *cursor)
{
	if (cursor->type == LXR_INPUT && cursor->next)
		cursor = node_add_input(target, cursor);
	else if (cursor->type == LXR_HEREDOC && cursor->next)
		cursor = node_add_heredoc(target, cursor);
	else if (cursor->type == LXR_OUTPUT && cursor->next)
		cursor = node_add_output(target, cursor);
	else if (cursor->type == LXR_APPEND && cursor->next)
		cursor = node_add_append(target, cursor);
	return (cursor);
}
