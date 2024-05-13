/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_raw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yushsato <yushsato@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 21:43:54 by yushsato          #+#    #+#             */
/*   Updated: 2024/05/13 16:50:02 by yushsato         ###   ########.fr       */
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
	char	**array;
	t_env	*env;
	t_env	*env_tmp;
	int		count;
	char	*tmp;

	env = *env_store();
	count = 0;
	env_tmp = NULL;
	while (env && ++count && ft_memcpy(&env_tmp, &env, sizeof(t_env *)))
		env = env->next;
	env = env_tmp;
	array = sf_calloc(sizeof(char *), count + 1);
	while (count > 0 && env)
	{
		tmp = ft_strjoin(env->key, "=");
		array[--count] = ft_strjoin(tmp, env->value);
		free(tmp);
		env = env->prev;
	}
	return (array);
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
	static const t_envc	env = {
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
