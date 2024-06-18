/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yushsato <yushsato@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 19:11:25 by yushsato          #+#    #+#             */
/*   Updated: 2024/06/18 01:13:04 by yushsato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		execute_run(t_token *head, char **envp);
pid_t	execute_async(char *const *argv, char *const *envp, t_io li, t_io ri);

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

t_execc	exec_constructor(void)
{
	static const t_execc	execc = {
		.async = execute_async,
		.await = await,
		.run = execute_run,
	};

	return (execc);
}
