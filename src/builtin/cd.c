/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsakanou <nsakanou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 17:52:41 by nsakanou          #+#    #+#             */
/*   Updated: 2024/06/22 18:10:18 by nsakanou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	check_file_permission(const char *path)
{
	if (access(path, F_OK) != -1)
	{
		if (access(path, R_OK) != 0)
			(ERR().exit)("cd", 1);
		if (access(path, X_OK) != 0)
			(ERR().exit)("cd", 1);
		return (0);
	}
	else
		(ERR().exit)("cd", 1);
	return (1);
}

static void	cd_home(void)
{
	char	*home_dir;

	home_dir = getenv("HOME");
	if (home_dir && chdir(home_dir) == 0)
		return ;
	else
		(ERR().exit)("cd", 1);
}

int	cd_command(char **argv)
{
	if (argv[1])
		check_file_permission(argv[1]);
	if (!argv[1])
		cd_home();
	if (chdir(argv[1]) != 0)
		(ERR().exit)("cd", 1);
	return (0);
}
