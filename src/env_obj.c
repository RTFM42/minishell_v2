/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_obj.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yushsato <yushsato@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 20:53:52 by yushsato          #+#    #+#             */
/*   Updated: 2024/06/08 00:19:01 by yushsato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
 * ## Environments store
 * @return	Pointer to chained environment objects
*/
t_env	**env_store(void)
{
	static t_env	*chain = NULL;

	return (&chain);
}

/**
 * ## Find an environment
 * @param	key An environment name
 * @return	Pointrt to found the environment (Nullable)
*/
t_env	*env_find(const char *key)
{
	t_env	*chain;

	chain = *env_store();
	while (key && chain)
	{
		if (!ft_memcmp(chain->key, key, ft_strlen(key) + 1))
			return (chain);
		else
			chain = chain->next;
	}
	return (NULL);
}

/**
 * ## Push an environment
 * @param	key An environment name
 * @param	value An environment value (Nullable)
 * @return	Pointer to pushed the environment
*/
t_env	*env_push(const char *key, const char *value)
{
	t_env	**store;
	t_env	*chain;

	store = env_store();
	if (env_find(key))
	{
		chain = env_find(key);
		chain->value = sf_strdup(value);
		return (chain);
	}
	if (key && *store == NULL)
	{
		*store = sf_calloc(1, sizeof(t_env));
		(*store)->key = sf_strdup(key);
		(*store)->value = sf_strdup(value);
		return (*store);
	}
	chain = *store;
	while (chain->next)
		chain = chain->next;
	chain->next = sf_calloc(1, sizeof(t_env));
	chain->next->key = sf_strdup(key);
	chain->next->value = sf_strdup(value);
	chain->next->prev = chain;
	return (chain->next);
}

/**
 * ## Set string array to env store
 * @param	list environment string array
 * @return	N/A
*/
void	env_set(char **list)
{
	char	*ptr;
	char	*key;
	int		count;
	t_env	*shlvl;

	count = 0;
	while (*list)
	{
		ptr = ft_strchr(*list, '=');
		key = sf_calloc(ptr - *list + 1, sizeof(char));
		key = ft_memcpy(key, *list, ptr - *list);
		if (*++ptr == '\0')
			env_push(key, NULL);
		else
			env_push(key, ptr);
		free(key);
		list++;
	}
	shlvl = env_find("SHLVL");
	ptr = shlvl->value;
	shlvl->value = ft_itoa(ft_strictatoi(shlvl->value) + 1);
	free(ptr);
}

/**
 * ## Delete an environment
 * @param	key An environment name
 * @return	`env_delete` returns status
 * @return	- `0`: sucess
 * @return	- `1`: failed
*/
int	env_delete(const char *key)
{
	t_env	*chain;

	chain = env_find(key);
	if (chain)
	{
		chain->prev->next = chain->next;
		chain->next->prev = chain->prev;
		free(chain->key);
		free(chain->value);
		free(chain);
		return (0);
	}
	return (1);
}
