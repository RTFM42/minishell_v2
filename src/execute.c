/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yushsato <yushsato@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 19:11:25 by yushsato          #+#    #+#             */
/*   Updated: 2024/05/24 14:17:09 by yushsato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	await(pid_t pid, int infd, int outfd)
{
	int	stat;

	if (waitpid(pid, &stat, 0) == pid)
	{
		if (WIFEXITED(stat))
			stat = WEXITSTATUS(stat);
		else if (WIFSIGNALED(stat))
			stat = WTERMSIG(stat);
		if (infd != STDIN_FILENO)
			close(infd);
		if (outfd != STDOUT_FILENO)
			close(outfd);
		return (stat);
	}
	return (1);
}

/**
 * ## Execute commands synchronously
 * @param	argv command path and args
 * @param	envp environment variables
 * @return	command status
 */
int	execute_sync(char *const *argv, char *const *envp)
{
	char	*path;
	pid_t	pid;

	if (argv == NULL || argv[0] == NULL)
		return (0);
	path = PATH().resolve(argv[0]);
	pid = fork();
	if (pid == -1)
		(ERR().exit)(__func__, 1);
	else if (pid == 0 && execve(path, argv, envp))
		(ERR().exit)(argv[0], 1);
	else
	{
		free(path);
		return (await(pid, STDIN_FILENO, STDOUT_FILENO));
	}
	return (1);
}

int	execute_pipe(char *const *argv, char *const *envp, int infd, int outfd)
{
	char	*path;
	pid_t	pid;

	if (argv == NULL || argv[0] == NULL)
		return (0);
	path = PATH().resolve(argv[0]);
	pid = fork();
	if (pid == -1)
		(ERR().exit)(__func__, 1);
	else if (pid == 0 && dup2(infd, STDIN_FILENO) != -1
		&& dup2(outfd, STDOUT_FILENO) != -1 && execve(path, argv, envp))
		(ERR().exit)(argv[0], 1);
	else
	{
		free(path);
		return (await(pid, infd, outfd));
	}
	return (1);
}

t_execc	exec_constructor(void)
{
	static const t_execc	execc = {
		.sync = execute_sync,
		.pipe = execute_pipe,
	};

	return (execc);
}
