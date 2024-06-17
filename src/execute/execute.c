/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yushsato <yushsato@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 19:11:25 by yushsato          #+#    #+#             */
/*   Updated: 2024/06/17 20:24:15 by yushsato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	execute_run(t_token *head, char **envp);

int	await(pid_t pid)
{
	int	stat;

	if (waitpid(pid, &stat, 0) == pid)
	{
		if (WIFEXITED(stat))
			stat = WEXITSTATUS(stat);
		else if (WIFSIGNALED(stat))
			stat = WTERMSIG(stat);
		return (stat);
	}
	return (1);
}

pid_t	execute_async(char *const *argv, char *const *envp, int *lp, int *rp)
{
	char	*path;
	pid_t	pid;

	if (argv == NULL || argv[0] == NULL)
		return (0);
	path = PATH().resolve(argv[0]);
	pid = fork();
	if (pid == -1)
		(ERR().exit)(__func__, 1);
	else if (pid == 0 && sf_close(lp[1]) >= 0 && sf_close(rp[0]) >= 0
		&& dup2(lp[0], STDIN_FILENO) != -1 && dup2(rp[1], STDOUT_FILENO) != -1
		&& execve(path, argv, envp))
		(ERR().exit)(argv[0], 1);
	else
		free(path);
	return (pid);
}

t_execc	exec_constructor(void)
{
	static const t_execc	execc = {
		.async = execute_async,
		.await = await,
		.run = execute_run,
	};

	return (execc);
}
