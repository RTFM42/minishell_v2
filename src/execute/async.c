/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   async.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yushsato <yushsato@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 01:12:08 by yushsato          #+#    #+#             */
/*   Updated: 2024/07/02 18:08:47 by yushsato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	close_pipe(int *pipe)
{
	if (pipe[0] != STDIN_FILENO)
		sf_close(pipe[0]);
	if (pipe[1] != STDOUT_FILENO)
		sf_close(pipe[1]);
	pipe[0] = STDIN_FILENO;
	pipe[1] = STDOUT_FILENO;
}

static void	exec(const char *file, char *const *argv, char *const *envp)
{
	if (!ft_memcmp(file, "env", 4))
		exit(1);
	execve(file, argv, envp);
}

int	await(pid_t pid)
{
	int	stat;

	if (waitpid(pid, &stat, 0) == pid)
	{
		if (WIFEXITED(stat))
			stat = WEXITSTATUS(stat);
		else if (WIFSIGNALED(stat))
			stat = WTERMSIG(stat) + 128;
		if (0 <= stat && stat <= 255)
			return (stat);
		else
			return (255);
	}
	return (1);
}

pid_t	async(char *const *argv, char *const *envp, int *ifp, int *ofp)
{
	pid_t	pid;
	char	*path;

	if (argv == NULL || argv[0] == NULL)
		return (0);
	pid = fork();
	path = PATH().resolve(argv[0]);
	if (pid == 0)
	{
		if (ifp[0] != STDIN_FILENO && dup2(ifp[0], STDIN_FILENO) != -1)
			close_pipe(ifp);
		else if (ifp[0] != STDIN_FILENO)
			(ERR().exit)("dup2", 1);
		if (ofp[1] != STDOUT_FILENO && dup2(ofp[1], STDOUT_FILENO) != -1)
			close_pipe(ofp);
		else if (ofp[1] != STDOUT_FILENO)
			(ERR().exit)("dup2", 1);
		exec(path, argv, envp);
		(ERR().exit)(argv[0], 1);
	}
	free(path);
	return (pid);
}
