/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_redirection_heredoc.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yushsato <yushsato@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 21:07:17 by yushsato          #+#    #+#             */
/*   Updated: 2024/06/18 19:59:55 by yushsato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#define C cursor
#define T target

char	*strallocat(char *dst, const char *add, int len);

static int	heredoc_concat(char *line, t_node *T, t_token *C)
{
	if (line && !ft_memcmp(line, C->token, C->len) && line[C->len] == '\0')
	{
		free(line);
		return (0);
	}
	if (line && *line == '\0')
	{
		ft_printf("wtf\n");
	}
	if (line == NULL)
	{
		ft_printf("warning: here-document delimited by end-of-file\n");
		return (0);
	}
	T->hdoc_str = strallocat(T->hdoc_str, line, ft_strlen(line));
	T->hdoc_str = strallocat(T->hdoc_str, "\n", 2);
	return (1);
}

t_token	*node_add_heredoc(t_node *T, t_token *C)
{
	SIG().herdoc(0);
	C = C->next;
	if (T->hdoc_str)
		free(T->hdoc_str);
	T->hdoc_str = ft_strdup("");
	while (1)
		if (!heredoc_concat(readline("> "), T, C))
			break ;
	T->last_input_type = LXR_HEREDOC;
	C = C->next;
	SIG().shell(0);
	return (C);
}
