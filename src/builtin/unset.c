/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsakanou <nsakanou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 16:54:46 by nsakanou          #+#    #+#             */
/*   Updated: 2024/07/06 17:21:47 by nsakanou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	bt_unset(int argc, char *const *argv, char *const *envp)
{
	int		i;
	t_env	*env;

	(void)envp;
	i = 1;
	while (i < argc)
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
