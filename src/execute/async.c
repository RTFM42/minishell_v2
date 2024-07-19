/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   async.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yushsato <yushsato@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 01:12:08 by yushsato          #+#    #+#             */
/*   Updated: 2024/07/20 00:57:11 by yushsato         ###   ########.fr       */
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

static int	puterr(const char *sh, const char *cmd, const char *reason)
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
	return (1);
}

static int	path_resolve_wrapper(char **d_fpath, const char *s_fname)
{
	struct stat	st;
	int			ret;

	ret = 0;
	*d_fpath = PATH().resolve(s_fname);
	if (path_builtin_inj(d_fpath, s_fname))
		return (1);
	if (!ft_strchr(*d_fpath, '/')
		&& puterr("minishell", s_fname, "command not found"))
		g_signal = 127;
	else if (stat(*d_fpath, &st) == -1 && errno == ENOENT && ((*s_fname == '.'
				&& !ft_strchr(s_fname, '/')) || ERR().print(s_fname)))
		g_signal = 127;
	else if ((st.st_mode & S_IFDIR && ERR().setno(EISDIR)
			&& ERR().print(s_fname))
		|| (access(*d_fpath, X_OK) == -1 && ERR().print(s_fname)))
		g_signal = 126;
	else
		ret++;
	if (!ret)
		free(*d_fpath);
	if (!ret)
		*d_fpath = NULL;
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
