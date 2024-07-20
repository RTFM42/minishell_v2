/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iofd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yushsato <yushsato@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 00:54:24 by yushsato          #+#    #+#             */
/*   Updated: 2024/07/21 00:58:03 by yushsato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	iofd_input(t_token *io, int *ifd)
{
	int		fd;

	fd = sf_fopen(io->token, O_RDONLY);
	if (fd != -1 && dup2(fd, ifd[0]) != -1)
		sf_close(fd);
	else if (ERR().print(io->token))
		return (-1);
	return (0);
}

static int	iofd_output(t_token *io, int *ofd)
{
	int	fd;

	fd = open(io->token, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd != -1 && dup2(fd, ofd[1]) != -1)
		sf_close(fd);
	else if (ERR().print(io->token))
		return (-1);
	return (0);
}

static int	iofd_append(t_token *io, int *ofd)
{
	int	fd;

	fd = open(io->token, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (fd != -1 && dup2(fd, ofd[1]) != -1)
		sf_close(fd);
	else if (ERR().print(io->token))
		return (-1);
	return (0);
}

int	exec_iofd(t_token *io, int *ifd, int *ofd, char **dhd)
{
	*dhd = NULL;
	ERR().setno(0);
	while (io)
	{
		if (!*dhd)
			free(*dhd);
		*dhd = NULL;
		if ((io->type == LXR_HEREDOC || io->type == LXR_INPUT) && ifd[0] == 0
			&& pipe(ifd) == -1 && ERR().print("pipe"))
			return (-1);
		if ((io->type == LXR_OUTPUT || io->type == LXR_APPEND) && ofd[1] == 1
			&& pipe(ofd) == -1 && ERR().print("pipe"))
			return (-1);
		if (io->type == LXR_HEREDOC)
			*dhd = ft_strdup(io->token);
		else if ((io->type == LXR_INPUT && iofd_input(io, ifd))
			|| (io->type == LXR_OUTPUT && iofd_output(io, ofd))
			|| (io->type == LXR_APPEND && iofd_append(io, ofd)))
			return (-1);
		io = io->next;
	}
	return (0);
}
