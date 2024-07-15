/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsakanou <nsakanou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 21:25:52 by nsakanou          #+#    #+#             */
/*   Updated: 2024/07/15 23:15:16 by nsakanou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	bt_cd(int argc, char *const *argv, char *const *envp);
int	bt_echo(int argc, char *const *argv, char *const *envp);
int	bt_pwd(int argc, char *const *argv, char *const *envp);
int	bt_env(int argc, char *const *argv, char *const *envp);
int	bt_unset(int argc, char *const *argv, char *const *envp);
int	bt_export(int argc, char *const *argv, char *const *envp);
int	bt_exit(int argc, char *const *argv, char *const *envp);

static int	ac(char *const *argv)
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
		status = bt_env(ac(argv), argv, envp);
	else if (!ft_memcmp(file, "cd", 3) && ++did)
		status = bt_cd(ac(argv), argv, envp);
	else if (!ft_memcmp(file, "echo", 5) && ++did)
		status = bt_echo(ac(argv), argv, envp);
	else if (!ft_memcmp(file, "pwd", 4) && ++did)
		status = bt_pwd(ac(argv), argv, envp);
	else if (!ft_memcmp(file, "unset", 6) && ++did)
		status = bt_unset(ac(argv), argv, envp);
	else if (!ft_memcmp(file, "export", 7) && ++did)
		status = bt_export(ac(argv), argv, envp);
	else if (!ft_memcmp(file, "exit", 5) && ++did)
		status = bt_exit(ac(argv), argv, envp);
	if (did)
		exit(status);
	return (0);
}

static int	builtin(char *const *argv, char *const *envp)
{
	if (!ft_memcmp(argv[0], "env", 4))
		return (bt_env(ac(argv), argv, envp));
	else if (!ft_memcmp(argv[0], "cd", 3))
		return (bt_cd(ac(argv), argv, envp));
	else if (!ft_memcmp(argv[0], "echo", 5))
		return (bt_echo(ac(argv), argv, envp));
	else if (!ft_memcmp(argv[0], "pwd", 4))
		return (bt_pwd(ac(argv), argv, envp));
	else if (!ft_memcmp(argv[0], "unset", 6))
		return (bt_unset(ac(argv), argv, envp));
	else if (!ft_memcmp(argv[0], "export", 7))
		return (bt_export(ac(argv), argv, envp));
	else if (!ft_memcmp(argv[0], "exit", 5))
		return (bt_exit(ac(argv), argv, envp));
	return (1);
}

int	exec_builtin(char *const *argv, char *const *envp, int *ofd)
{
	int	status;
	int	outfd;

	if (ofd[1] != 1)
		outfd = dup(1);
	if (ofd[1] != 1 && (outfd < 0 || dup2(ofd[1], 1) == -1))
		ERR().print("minishell");
	status = builtin(&argv[0], envp);
	if (ofd[1] != STDOUT_FILENO && outfd > -1)
		dup2(outfd, 1);
	return (status);
}
