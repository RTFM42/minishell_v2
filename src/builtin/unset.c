/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsakanou <nsakanou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 17:53:20 by nsakanou          #+#    #+#             */
/*   Updated: 2024/06/26 16:15:37 by nsakanou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	unset_command(char **argv)
{
	size_t	i;
	t_env	*env;

	i = 1;
	while (argv[i])
	{
		env = *(ENV().store());
		if (env_name_judge(argv[i]))
		{
			while (env)
			{
				if (ft_strcmp(env->key, argv[i]) == 0
					&& ENV().delete(argv[i]) == 0)
					break ;
				env = env->next;
			}
		}
		else
			ERR().print("unset");
		i++;
	}
	return (0);
}