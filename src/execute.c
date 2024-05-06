/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yushsato <yushsato@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 19:11:25 by yushsato          #+#    #+#             */
/*   Updated: 2024/05/06 13:51:59 by yushsato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
 * ## Execute commands synchronously
 * @param	cmds command path and args
*/
int	execute_sync(char **cmds)
{
	pid_t	pid;
	int		stat;

	pid = fork();
	stat = 0;
	sig_sh(0);
	if (pid == 0)
		execve(cmds[0], &cmds[1], envraw_get());
	else if (pid < 0)
		return (sf_errexit(__func__));
	wait(&stat);
	if (WIFEXITED(stat))
		stat = WEXITSTATUS(stat);
	else if (WIFSIGNALED(stat))
		stat = WTERMSIG(stat);
	return (stat);
}
