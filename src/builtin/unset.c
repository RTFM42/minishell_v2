/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yushsato <yushsato@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 16:54:46 by nsakanou          #+#    #+#             */
/*   Updated: 2024/07/17 03:54:03 by yushsato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	bt_unset(int argc, char *const *argv, char *const *envp)
{
	int		i;

	(void)envp;
	i = 1;
	while (i < argc)
	{
		if (ENV().find(argv[i]))
			ENV().delete(argv[i]);
		else if (errno != 0)
			ERR().print("unset");
		i++;
	}
	return (0);
}
