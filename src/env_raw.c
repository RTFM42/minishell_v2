/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_raw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yushsato <yushsato@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 21:43:54 by yushsato          #+#    #+#             */
/*   Updated: 2024/04/27 03:18:25 by yushsato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	***envraw_store(void)
{
	static char	**env_raw = NULL;

	return (&env_raw);
}

char const	**envraw_get(void)
{
	char	**env_raw;

	envraw_refresh();
	env_raw = *envraw_store();
	return ((char const **)env_raw);
}

static void	envraw_free(void)
{
	char	***penv_raw;
	char	**env_raw;

	penv_raw = envraw_store();
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

char	**envraw_refresh(void)
{
	char	***penv_raw;
	char	**env_raw;
	t_env	*env;
	int		count;
	char	*tmp;

	envraw_free();
	penv_raw = envraw_store();
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
