/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   promise.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsakanou <nsakanou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 19:44:09 by yushsato          #+#    #+#             */
/*   Updated: 2024/07/16 00:35:24 by nsakanou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	await(pid_t pid);

static pid_t	**promise_store(void)
{
	static pid_t	*pids = NULL;

	return (&pids);
}

void	promise_rm(void)
{
	pid_t	**store;
	pid_t	*pids;
	pid_t	*new;
	int		i;

	i = 0;
	store = promise_store();
	pids = *store;
	while (pids && pids[i])
		i++;
	if (i == 0)
	{
		if (pids)
			free(pids);
		*store = NULL;
		return ;
	}
	new = sf_calloc(i, sizeof(pid_t));
	ft_memcpy(new, pids + 1, sizeof(pid_t) * i);
	if (pids)
		free(pids);
	*store = new;
}

void	promise_add(pid_t pid)
{
	pid_t	**store;
	pid_t	*pids;
	pid_t	*new;
	int		i;

	i = 0;
	store = promise_store();
	pids = *store;
	while (pids && pids[i])
		i++;
	new = sf_calloc(i + 2, sizeof(pid_t));
	ft_memcpy(new, pids, sizeof(pid_t) * i);
	new[i] = pid;
	free(pids);
	*store = new;
}

int	promise_all(void)
{
	int		stats;
	pid_t	*pids;
	pid_t	now;

	stats = 0;
	pids = *promise_store();
	while (pids && *pids > 0)
	{
		stats = 1;
		now = *pids;
		promise_rm();
		if (now != -1)
			stats = await(now);
		pids = *promise_store();
	}
	return (stats);
}
