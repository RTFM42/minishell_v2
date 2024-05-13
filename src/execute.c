/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yushsato <yushsato@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 19:11:25 by yushsato          #+#    #+#             */
/*   Updated: 2024/05/11 19:56:37 by yushsato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
 * ## Execute commands synchronously
 * @param	argv command path and args
 * @return	command status
 */
int	execute_sync(char *const *argv, char *const *envp)
{
	pid_t		pid;
	int			stat;
	const char	*file;

	pid = fork();
	stat = 0;
	(void)envp;
	if (pid == -1)
		sf_exit(__func__, 1);
	else if (pid == 0)
	{

		
		int	count = 0;
		while (envp[count])
		{
			ft_printf("child [%d]: %s\n", count, envp[count]);
			count++;
		}

		
		printf("child: %d\n", execve(argv[0], argv, NULL));
		sf_error(file);
	}
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
