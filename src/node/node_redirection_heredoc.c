/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_redirection_heredoc.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yushsato <yushsato@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 21:07:17 by yushsato          #+#    #+#             */
/*   Updated: 2024/07/23 19:34:39 by yushsato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#define C cursor
#define T target

char	*strallocat(char *dst, const char *add, int len);
t_token	*token_push(t_token *head, char *token, int len, int type);
t_token	*token_last(t_token *head);

static int	heredoc_read(t_token *token, t_node *T, t_token *C)
{
	char	*line;

	line = readline("> ");
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
	else if (SIG().get() != 0 && ft_printf("\n"))
	{
		if (line)
			free(line);
		T->cancel = g_signal;
		return (-1);
	}
	token->token = strallocat(token->token, line, ft_strlen(line));
	token->token = strallocat(token->token, "\n", 2);
	if (line)
		free(line);
	return (1);
}

t_token	*node_add_heredoc(t_node *T, t_token *C)
{
	int		status;
	int		fd;
	t_token	*last;

	SIG().herdoc(0);
	C = C->next;
	T->io_tokens = token_push(T->io_tokens, "", 0, LXR_HEREDOC);
	fd = dup(STDIN_FILENO);
	last = token_last(T->io_tokens);
	while (1)
	{
		status = -1;
		status = heredoc_read(last, T, C);
		if (status <= 0)
			break ;
	}
	last->len = ft_strlen(last->token);
	if (status == -1)
		dup2(fd, STDIN_FILENO);
	else
		close(fd);
	C = C->next;
	SIG().shell(0);
	return (C);
}
