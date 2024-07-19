/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   await.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yushsato <yushsato@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 00:57:21 by yushsato          #+#    #+#             */
/*   Updated: 2024/07/20 00:57:24 by yushsato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	if (pid == 0)
		return (g_signal);
	return (1);
}
