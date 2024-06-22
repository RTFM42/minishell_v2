/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsakanou <nsakanou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 21:41:00 by nsakanou          #+#    #+#             */
/*   Updated: 2024/06/22 19:56:50 by nsakanou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static void	export_insert_plus(t_env *env, char *value)
{
	char	*temp;

	temp = env->value;
	env->value = ft_strjoin(env->value, value);
	free(temp);
}

static void	export_rewrite_value(t_env *env, char *name, char *new_value)
{
	if (env == NULL || name == NULL || new_value == NULL)
		return ;
	while (env)
	{
		if (env->key && ft_strcmp(env->key, name) == 0)
		{
			if (env->value)
				free(env->value);
			env->value = ft_strdup(new_value);
			return ;
		}
		env = env->next;
	}
}

static char	check_type(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return ('=');
		else if (str[i] == '+' && str[i + 1] == '=')
			return ('+');
		i++;
	}
	return (0);
}

int	export_insert(char *arg, t_env *env)
{
	char	*name;
	char	*value;

	name = export_getname(arg);
	value = export_getvalue(arg);
	env = env_find(env, name);
	if (name == NULL)
		return (1);
	else if (check_type(arg) == '=' && env == NULL)
		env_push(env_store(), value);
	else if (check_type(arg) == '=')
		export_rewrite_value(*env_store(), name, value);
	else if (check_type(arg) == '+' && env == NULL)
		env_list_add(env_store(), name, value);
	else if (check_type(arg) == '+')
		export_insert_plus(env, value);
	else if (check_type(arg) == 0 && env == NULL)
		env_list_add(env_store(), name, NULL);
	free(name);
	free(value);
	return (0);
}
