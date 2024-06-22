/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsakanou <nsakanou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 17:53:09 by nsakanou          #+#    #+#             */
/*   Updated: 2024/06/22 20:01:15 by nsakanou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	export_command(char **argv)
{
	t_env	*env;
	int		ret;

	ret = 0;
	env = (ENV().store)->next;
	if (ft_memcpy(&env, &(*env_store())->next, sizeof(void *)) && !argv[1])
		export_sortenvs(env);
	while (env_update("?", ft_itoa(ret)) && *++argv)
		if (export_insert(*argv, env))
			ret = 1;
	return (ret);
}
