/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yushsato <yushsato@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 19:44:35 by yushsato          #+#    #+#             */
/*   Updated: 2024/06/18 15:40:55 by yushsato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#define C cursor
#define T target

char	**strsallocat(char **ary, char *add);
t_token	*node_add_heredoc(t_node *T, t_token *C);

t_token	*node_add_input(t_node *T, t_token *C)
{
	C = C->next;
	if (T->input_fname)
		free(T->input_fname);
	T->input_fname = ft_strdup(C->token);
	T->last_input_type = LXR_INPUT;
	C = C->next;
	return (C);
}

t_token	*node_add_output(t_node *T, t_token *C)
{
	C = C->next;
	if (T->output_fname)
		free(T->output_fname);
	T->output_fname = ft_strdup(C->token);
	T->last_output_type = LXR_OUTPUT;
	C = C->next;
	return (C);
}

t_token	*node_add_append(t_node *T, t_token *C)
{
	C = C->next;
	if (T->append_fname)
		free(T->append_fname);
	T->append_fname = ft_strdup(C->token);
	T->last_output_type = LXR_APPEND;
	C = C->next;
	return (C);
}

t_token	*node_add_redirection(t_node *T, t_token *C)
{
	if (C->type == LXR_INPUT && C->next)
		C = node_add_input(T, C);
	else if (C->type == LXR_HEREDOC && C->next)
		C = node_add_heredoc(T, C);
	else if (C->type == LXR_OUTPUT && C->next)
		C = node_add_output(T, C);
	else if (C->type == LXR_APPEND && C->next)
		C = node_add_append(T, C);
	else if (C->type >= LXR_PIPE)
	{
		if (C->type == LXR_PIPE)
			T->last_input_type = LXR_PIPE;
		C = C->next;
	}
	return (C);
}
