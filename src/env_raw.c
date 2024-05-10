/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_raw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yushsato <yushsato@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 21:43:54 by yushsato          #+#    #+#             */
/*   Updated: 2024/05/09 22:07:37 by yushsato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	**env_store(void);
void	env_set(char **list);
t_env	*env_find(const char *key);
t_env	*env_push(const char *key, const char *value);
int		env_delete(const char *key);

char	**env_dump(void)
{
	char	**env_raw;
	t_env	*env;
	int		count;
	char	*tmp;

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
	return (env_raw);
}

void	env_free(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		free(envp[i++]);
	free(envp);
}

t_envc	env_constructor(void)
{
	const static t_envc	env = {
		.store = env_store,
		.set = env_set,
		.find = env_find,
		.push = env_push,
		.delete = env_delete,
		.dump = env_dump,
		.free = env_free,
	};

	return (env);
}
