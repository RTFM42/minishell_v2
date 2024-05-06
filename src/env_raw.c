/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_raw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yushsato <yushsato@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 21:43:54 by yushsato          #+#    #+#             */
/*   Updated: 2024/05/06 23:25:39 by yushsato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	***store(void)
{
	static char	**env_raw = NULL;

	return (&env_raw);
}

static void	rawfree(void)
{
	char	***penv_raw;
	char	**env_raw;

	penv_raw = store();
	if (*penv_raw == NULL)
		return ;
	env_raw = *penv_raw;
	while (*env_raw)
	{
		free(*env_raw);
		env_raw++;
	}
	free(env_raw);
	*penv_raw = NULL;
}

char	**refresh(void)
{
	char	***penv_raw;
	char	**env_raw;
	t_env	*env;
	int		count;
	char	*tmp;

	rawfree();
	penv_raw = store();
	env_raw = *penv_raw;
	env = *env_store();
	count = 0;
	while (env && env->next && ++count)
		env = env->next;
	env_raw = sf_calloc(sizeof(char *), count + 1);
	while (count + 1 > 0)
	{
		tmp = ft_strjoin(env->key, "=");
		env_raw[count] = ft_strjoin(tmp, env->value);
		free(tmp);
		env = env->prev;
		count--;
	}
	*penv_raw = env_raw;
	return (env_raw);
}

char *const	*list(void)
{
	char	**env_raw;

	refresh();
	env_raw = *store();
	return ((char *const *)env_raw);
}

t_envraw	envraw_constructor(void)
{
	const static t_envraw	envraw = {
		.list = list,
		.refresh = refresh,
	};

	return (envraw);
}
