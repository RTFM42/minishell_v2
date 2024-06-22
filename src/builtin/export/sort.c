/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsakanou <nsakanou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 20:00:47 by nsakanou          #+#    #+#             */
/*   Updated: 2024/06/22 20:03:41 by nsakanou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static t_env	*envcpy(t_env *env)
{
	t_env	*copy;
	t_env	*prev;
	t_env	*head;

	prev = NULL;
	while (env)
	{
		copy = ft_calloc(1, sizeof(t_env));
		ft_memcpy(copy, env, sizeof(t_env));
		if (prev != NULL)
			prev->next = copy;
		else
			head = copy;
		env = env->next;
		copy->next = NULL;
		prev = copy;
	}
	return (head);
}

static t_env	*export_putenv(t_env *env)
{
	if (!ft_memcmp(env->key, "_", 2)
		|| !(ft_isalpha(env->key[0]) || env->key[0] == '_'))
		return (env);
	if (env->value)
		printf("declare -x %s=\"%s\"\n", env->key, env->value);
	else
		printf("declare -x %s\n", env->key);
	return (env);
}

static t_env	*export_swap(t_env *env)
{
	char	*tmp;

	ft_memcpy(&tmp, &env->key, sizeof(void *));
	ft_memcpy(&env->key, &env->next->key, sizeof(void *));
	ft_memcpy(&env->next->key, &tmp, sizeof(void *));
	ft_memcpy(&tmp, &env->value, sizeof(void *));
	ft_memcpy(&env->value, &env->next->value, sizeof(void *));
	ft_memcpy(&env->next->value, &tmp, sizeof(void *));
	return (env);
}

void	export_sortenvs(t_env *env)
{
	t_env	*copy;
	t_env	*prev;
	t_env	*head;
	int		i;

	copy = envcpy(env);
	head = copy;
	prev = NULL;
	i = 1;
	while (i && ft_memset(&i, 0, sizeof(int)))
	{
		while (copy && copy->next)
		{
			if (ft_strcmp(copy->key, copy->next->key) > 0
				&& export_swap(copy))
				i++;
			copy = copy->next;
		}
		copy = head;
	}
	while (copy && export_putenv(copy))
		copy = copy->next;
	while (copy && ft_memcpy(&prev, &copy, sizeof(void *))
		&& ft_memcpy(&copy, &copy->next, sizeof(void *)))
		free(prev);
}
