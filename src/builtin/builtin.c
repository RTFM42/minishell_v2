/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsakanou <nsakanou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 13:11:27 by nsakanou          #+#    #+#             */
/*   Updated: 2024/06/22 15:59:14 by nsakanou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	exec_builtin(char **argv)
{
	if (ft_memcmp(argv[0], "echo", 5) == 0)
		echo_command(argv);
	else if (ft_memcmp(argv[0], "cd", 3) == 0)
		cd_command(argv);
	else if (ft_memcmp(argv[0], "pwd", 4) == 0)
		pwd_command(NULL);
	else if (ft_memcmp(argv[0], "unset", 6) == 0)
		unset_command(argv);
	else if (ft_memcmp(argv[0], "export", 7) == 0)
		export_command(argv);
	else if (ft_memcmp(argv[0], "env", 4) == 0)
		env_command();
	else if (ft_memcmp(argv[0], "exit", 5) == 0)
		exit_command(argv);
	return (256);
}
