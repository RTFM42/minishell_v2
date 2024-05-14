/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yushsato <yushsato@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 19:11:25 by yushsato          #+#    #+#             */
/*   Updated: 2024/05/14 15:28:21 by yushsato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// char	*resolve_path(const char *bin)
// {
	
// }

/**
 * ## Execute commands synchronously
 * @param	argv command path and args
 * @param	envp environment variables
 * @return	command status
 */
int	execute_sync(char *const *argv, char *const *envp)
{
	pid_t		pid;
	int			stat;

	pid = fork();
	stat = 0;
	if (pid == -1)
		(ERR().exit)(__func__, 1);
	else if (pid == 0 && execve(argv[0], argv, envp))
		(ERR().exit)(argv[0], 1);
	else if (waitpid(pid, &stat, 0) == pid)
	{
		if (WIFEXITED(stat))
			stat = WEXITSTATUS(stat);
		else if (WIFSIGNALED(stat))
			stat = WTERMSIG(stat);
		return (stat);
	}
	return (1);
}

t_execc	exec_constructor(void)
{
	static const t_execc	execc = {
		.sync = execute_sync,
	};

	return (execc);
}
