/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   async.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yushsato <yushsato@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 01:12:08 by yushsato          #+#    #+#             */
/*   Updated: 2024/06/19 16:25:18 by yushsato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ea_input(char *fname)
{
	const int	ifd = open(fname, O_RDONLY);

	if (ifd < 0)
		(ERR().exit)(fname, 1);
	dup2(ifd, STDIN_FILENO);
}

void	ea_output(char *fname)
{
	const int	ofd = open(fname, O_CREAT | O_RDWR | O_TRUNC, 0644);

	if (ofd < 0)
		(ERR().exit)(fname, 1);
	dup2(ofd, STDOUT_FILENO);
}

void	ea_append(char *fname)
{
	const int	ofd = open(fname, O_CREAT | O_RDWR | O_APPEND, 0644);

	if (ofd < 0)
		(ERR().exit)(fname, 1);
	dup2(ofd, STDOUT_FILENO);
}

static void	shell_io(t_io li, t_io ri)
{
	if (li.type == LXR_INPUT)
		ea_input(li.info);
	else if ((li.type == LXR_PIPE || li.type == LXR_HEREDOC)
		&& dup2(li.pipe[0], STDIN_FILENO) > -1)
		sf_close(li.pipe[1]);
	if (ri.type == LXR_OUTPUT)
		ea_output(ri.info);
	else if (ri.type == LXR_APPEND)
		ea_append(ri.info);
	else if (ri.type == LXR_PIPE && dup2(ri.pipe[1], STDOUT_FILENO) > -1)
		sf_close(ri.pipe[0]);
}

pid_t	execute_async(char *const *argv, char *const *envp, t_io li, t_io ri)
{
	char	*path;
	pid_t	pid;

	if (argv == NULL || argv[0] == NULL)
		return (0);
	path = PATH().resolve(argv[0]);
	pid = fork();
	if (pid == 0)
	{
		shell_io(li, ri);
		execve(path, argv, envp);
		(ERR().exit)(argv[0], 1);
	}
	if (pid == -1)
		ERR().print(argv[0]);
	free(path);
	return (pid);
}
