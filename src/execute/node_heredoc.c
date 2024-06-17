/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yushsato <yushsato@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 21:07:17 by yushsato          #+#    #+#             */
/*   Updated: 2024/06/17 21:12:40 by yushsato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#define C cursor
#define T target

static int	heredoc_concat(char *line, t_node *T, t_token *C)
{
	if (line && !ft_memcmp(line, C->token, C->len) && line[C->len] == '\0')
	{
		free(line);
		return (0);
	}
	if (line && *line == NULL)
	{
		free(line);
		ft_printf("warning: here-document delimited by end-of-file");
		T->cancel = 1;
		return (0);
	}
	if (line == NULL)
	{
		T->cancel = 1;
		return (0);
	}
	T->hdoc_str = strallocat(T->hdoc_str, line, ft_strlen(line));
	return (1);
}

t_token	*node_add_heredoc(t_node *T, t_token *C)
{
	char	*line;

	C = C->next;
	if (T->hdoc_str)
		free(T->hdoc_str);
	T->hdoc_str = NULL;
	SIG().herdoc(0);
	while (1)
		if (!heredoc_concat(readline("> "), T, C))
			break ;
	SIG().shell(0);
	T->last_input_type = LXR_HEREDOC;
	C = C->next;
	return (C);
}
