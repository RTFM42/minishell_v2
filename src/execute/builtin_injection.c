/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_injection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yushsato <yushsato@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 14:58:28 by yushsato          #+#    #+#             */
/*   Updated: 2024/07/13 18:14:32 by yushsato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	bt_cd(int argc, char *const *argv, char *const *envp);
int	bt_echo(int argc, char *const *argv, char *const *envp);
int	bt_pwd(int argc, char *const *argv, char *const *envp);
int	bt_env(int argc, char *const *argv, char *const *envp);

int	isbuiltin(const char *fname)
{
	if (!ft_memcmp(fname, "echo", 5) || !ft_memcmp(fname, "cd", 3)
		|| !ft_memcmp(fname, "pwd", 4) || !ft_memcmp(fname, "export", 7)
		|| !ft_memcmp(fname, "unset", 6) || !ft_memcmp(fname, "env", 4)
		|| !ft_memcmp(fname, "exit", 5))
		return (1);
	return (0);
}

int	path_builtin_inj(char **d_fpath, const char *s_fname)
{
	char	*inj;
	int		ret;

	inj = NULL;
	ret = 0;
	if (isbuiltin(s_fname))
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
	else if (!ft_memcmp(file, "cd", 3) && ++did)
		status = bt_cd(argv_count(argv), argv, envp);
	else if (!ft_memcmp(file, "echo", 5) && ++did)
		status = bt_echo(argv_count(argv), argv, envp);
	else if (!ft_memcmp(file, "pwd", 4) && ++did)
		status = bt_pwd(argv_count(argv), argv, envp);
	if (did)
		exit(status);
	return (0);
}

int	exec_builtin(char *const *argv, char *const *envp, int *ofd)
{
	int	did;
	int	status;
	int	outfd;

	did = 0;
	if (ofd[1] != 1)
		outfd = dup(1);
	if (ofd[1] != 1 && (outfd < 0 || dup2(ofd[1], 1) == -1))
		ERR().print("minishell");
	if (!ft_memcmp(argv[0], "env", 4) && ++did)
		status = bt_env(argv_count(argv), argv, envp);
	else if (!ft_memcmp(argv[0], "cd", 3) && ++did)
		status = bt_cd(argv_count(argv), argv, envp);
	else if (!ft_memcmp(argv[0], "echo", 5) && ++did)
		status = bt_echo(argv_count(argv), argv, envp);
	else if (!ft_memcmp(argv[0], "pwd", 4) && ++did)
		status = bt_pwd(argv_count(argv), argv, envp);
	if (ofd[1] != STDOUT_FILENO && outfd > -1)
		dup2(outfd, 1);
	if (did)
		return (status);
	return (1);
}
