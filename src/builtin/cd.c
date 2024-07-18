/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsakanou <nsakanou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 16:46:48 by nsakanou          #+#    #+#             */
/*   Updated: 2024/07/18 20:42:01 by nsakanou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	check_file_permission(const char *path)
{
	if (access(path, F_OK) != -1)
	{
		if (access(path, R_OK) != 0)
			(ERR().print)("cd");
		if (access(path, X_OK) != 0)
			(ERR().print)("cd");
		return (0);
	}
	else
		(ERR().print)("cd");
	return (1);
}

static void	cd_home(void)
{
	char	*home_dir;

	home_dir = getenv("HOME");
	if (home_dir && !chdir(home_dir))
		return ;
	else
		(ERR().print)("cd");
}

int	bt_cd(int argc, char *const *argv, char *const *envp)
{
	(void)envp;
	if (argc == 0)
		cd_home();
	if (argc > 2)
	{
		ft_putendl_fd("minishell: cd: too many arguments", 2);
		return (0);
	}
	if (argv[1] && check_file_permission(argv[1]))
		return (1);
	else if (chdir(argv[1]) != 0)
	{
		(ERR().print)("cd");
		return (1);
	}
	return (0);
}
