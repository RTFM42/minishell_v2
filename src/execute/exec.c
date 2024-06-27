/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yushsato <yushsato@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 19:11:25 by yushsato          #+#    #+#             */
/*   Updated: 2024/06/27 14:59:53 by yushsato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		execute_run(t_token *head, char **envp);
pid_t	async(char *const *argv, char *const *envp, int *ifp, int *ofp);
void	promise_add(pid_t pid);
int		promise_all(void);

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
		.async = async,
		.await = await,
		.promise_add = promise_add,
		.promise_all = promise_all,
		.run = execute_run,
	};

	return (execc);
}
