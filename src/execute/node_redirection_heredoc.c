/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_redirection_heredoc.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yushsato <yushsato@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 21:07:17 by yushsato          #+#    #+#             */
/*   Updated: 2024/06/19 16:37:20 by yushsato         ###   ########.fr       */
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
	if (line == NULL && SIG().get() == 0)
	{
		ft_printf("warning: here-document delimited by end-of-file\n");
		return (0);
	}
	else if (SIG().get() != 0)
	{
		ft_printf("\n");
		T->cancel = g_signal;
		return (-1);
	}
	T->hdoc_str = strallocat(T->hdoc_str, line, ft_strlen(line));
	T->hdoc_str = strallocat(T->hdoc_str, "\n", 2);
	return (1);
}

t_token	*node_add_heredoc(t_node *T, t_token *C)
{
	int	status;
	int	fd;

	SIG().herdoc(0);
	SIG().set(0);
	C = C->next;
	if (T->hdoc_str)
		free(T->hdoc_str);
	T->hdoc_str = ft_strdup("");
	fd = dup(STDIN_FILENO);
	while (1)
	{
		status = heredoc_concat(readline("> "), T, C);
		if (status <= 0)
			break ;
	}
	if (status == -1)
		dup2(fd, STDIN_FILENO);
	else
		close(fd);
	T->last_input_type = LXR_HEREDOC;
	C = C->next;
	SIG().shell(0);
	return (C);
}
