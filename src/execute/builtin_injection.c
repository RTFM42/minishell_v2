/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_injection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yushsato <yushsato@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 14:58:28 by yushsato          #+#    #+#             */
/*   Updated: 2024/07/06 16:26:28 by yushsato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	bt_env(int argc, char *const *argv, char *const *envp);

int	path_builtin_inj(char **d_fpath, const char *s_fname)
{
	char	*inj;
	int		ret;

	inj = NULL;
	ret = 0;
	if (!ft_memcmp(s_fname, "echo", 5) || !ft_memcmp(s_fname, "cd", 3)
		|| !ft_memcmp(s_fname, "pwd", 4) || !ft_memcmp(s_fname, "export", 6)
		|| !ft_memcmp(s_fname, "unset", 6) || !ft_memcmp(s_fname, "env", 4)
		|| !ft_memcmp(s_fname, "exit", 5))
		inj = ft_strdup(s_fname);
	if (inj != NULL)
	{
		free(*d_fpath);
		*d_fpath = inj;
		ret++;
	}
	return (ret);
}

static int	argv_count(char *const *argv)
{
	int	i;

	i = 0;
	while (argv[i])
		i++;
	return (i);
}

int	exec_builtin_inj(const char *file, char *const *argv, char *const *envp)
{
	int	did;
	int	status;

	did = 0;
	if (!ft_memcmp(file, "env", 4) && ++did)
		status = bt_env(argv_count(argv), argv, envp);
	if (did)
		exit(status);
	return (0);
}
