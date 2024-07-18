/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   async.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yushsato <yushsato@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 01:12:08 by yushsato          #+#    #+#             */
/*   Updated: 2024/07/19 03:07:52 by yushsato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	path_builtin_inj(char **d_fpath, const char *s_fname);
int	exec_builtin_inj(const char *file, char *const *argv, char *const *envp);

void	close_pipe(int *pipe)
{
	if (pipe[0] != STDIN_FILENO)
		sf_close(pipe[0]);
	if (pipe[1] != STDOUT_FILENO)
		sf_close(pipe[1]);
}

int	await(pid_t pid)
{
	int	stat;

	if (waitpid(pid, &stat, 0) == pid)
	{
		if (WIFEXITED(stat))
			stat = WEXITSTATUS(stat);
		else if (WIFSIGNALED(stat))
			stat = WTERMSIG(stat) + 128;
		if (0 <= stat && stat <= 255)
			return (stat);
		else
			return (255);
	}
	if (pid == 0)
		return (g_signal);
	return (1);
}

static void	puterr(const char *sh, const char *cmd, const char *reason)
{
	char	*ret;
	char	*tmp;

	ret = ft_strjoin(sh, ": ");
	tmp = ret;
	ret = ft_strjoin(tmp, cmd);
	free(tmp);
	tmp = ret;
	ret = ft_strjoin(tmp, ": ");
	free(tmp);
	tmp = ret;
	ret = ft_strjoin(tmp, reason);
	free(tmp);
	tmp = ret;
	ret = ft_strjoin(tmp, "\n");
	free(tmp);
	ft_putstr_fd(ret, 2);
	free(ret);
}

static int	path_resolve_wrapper(char **d_fpath, const char *s_fname)
{
	struct stat	st;
	int			ret;

	ret = 0;
	*d_fpath = PATH().resolve(s_fname);
	if (path_builtin_inj(d_fpath, s_fname))
		return (1);
	if (!ft_strchr(*d_fpath, '/'))
	{
		g_signal = 127;
		puterr("minishell", s_fname, "command not found");
	}
	else if (stat(*d_fpath, &st) == -1 && errno == ENOENT)
	{
		g_signal = 127;
		if (*s_fname == '.' && !ft_strchr(s_fname, '/'))
			puterr("minishell", s_fname, "command not found");
		else
			ERR().print(s_fname);
	}
	else if (st.st_mode & S_IFDIR && ERR().setno(EISDIR))
	{
		g_signal = 126;
		ERR().print(s_fname);
	}
	else if (access(*d_fpath, X_OK) == -1)
	{
		g_signal = 126;
		ERR().print(s_fname);
	}
	else
		ret++;
	if (!ret)
	{
		free(*d_fpath);
		*d_fpath = NULL;
	}
	return (ret);
}

static int	dup2_exit(void)
{
	(ERR().exit)("dup2", 1);
	return (1);
}

pid_t	async(char *const *av, char *const *envp, int *ifp, int *ofp)
{
	pid_t	pid;
	char	*path;

	if (av == NULL || av[0] == NULL || !path_resolve_wrapper(&path, av[0]))
		return (0);
	pid = fork();
	if (pid == 0)
	{
		if (ifp[0] != 0 && (dup2(ifp[0], 0) != -1 || dup2_exit()))
			close_pipe(ifp);
		if (ofp[1] != 1 && (dup2(ofp[1], 1) != -1 || dup2_exit()))
			close_pipe(ofp);
		if (!exec_builtin_inj(path, av, envp))
			execve(path, av, envp);
		(ERR().exit)(av[0], 1);
	}
	free(path);
	return (pid);
}
