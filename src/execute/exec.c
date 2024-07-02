/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yushsato <yushsato@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 19:11:25 by yushsato          #+#    #+#             */
/*   Updated: 2024/07/02 18:03:31 by yushsato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		execute_run(t_token *head, char **envp);
int		await(pid_t pid);
pid_t	async(char *const *argv, char *const *envp, int *ifp, int *ofp);
void	promise_add(pid_t pid);
int		promise_all(void);

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
