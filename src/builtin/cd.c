/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yushsato <yushsato@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 16:46:48 by nsakanou          #+#    #+#             */
/*   Updated: 2024/07/20 00:14:05 by yushsato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	check_file_permission(const char *path)
{
	char	*tmp;
	int		ret;

	tmp = ft_strjoin("cd: ", path);
	ret = 0;
	if (access(path, F_OK) != -1)
	{
		if (access(path, R_OK) == -1 && ++ret)
			(ERR().print)(tmp);
		if (access(path, X_OK) == -1 && ++ret)
			(ERR().print)(tmp);
		free(tmp);
		return (!!ret);
	}
	(ERR().print)(tmp);
	free(tmp);
	return (1);
}

static int	cd_home(void)
{
	char	*home_dir;

	home_dir = getenv("HOME");
	if (home_dir && chdir(home_dir) != -1)
		return (0);
	else
	{
		(ERR().print)("cd");
		return (1);
	}
}

int	bt_cd(int argc, char *const *argv, char *const *envp)
{
	char	*tmp;

	(void)envp;
	if (argc == 1)
		return (cd_home());
	else if (argc > 2)
	{
		ft_putendl_fd("minishell: cd: too many arguments", 2);
		return (1);
	}
	if (argv[1] && check_file_permission(argv[1]))
		return (1);
	else if (chdir(argv[1]) == -1)
	{
		tmp = ft_strjoin("cd: ", argv[1]);
		ERR().print(tmp);
		free(tmp);
		return (1);
	}
	return (0);
}
