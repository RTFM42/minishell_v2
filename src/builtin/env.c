/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsakanou <nsakanou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 17:52:59 by nsakanou          #+#    #+#             */
/*   Updated: 2024/06/22 19:41:49 by nsakanou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	env_command(void)
{
	char	**envs;
	int		i;

	envs = ENV().dump();
	i = 0;
	while (envs[i])
		printf("%s\n", envs[i]);
	ENV().free(envs);
	return (0);
}
