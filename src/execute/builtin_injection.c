/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_injection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsakanou <nsakanou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 14:58:28 by yushsato          #+#    #+#             */
/*   Updated: 2024/07/15 21:29:17 by nsakanou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	isbuiltin(const char *fname)
{
	if (!ft_memcmp(fname, "echo", 5) || !ft_memcmp(fname, "cd", 3)
		|| !ft_memcmp(fname, "pwd", 4) || !ft_memcmp(fname, "export", 7)
		|| !ft_memcmp(fname, "unset", 6) || !ft_memcmp(fname, "env", 4)
		|| !ft_memcmp(fname, "exit", 5))
		return (1);
	return (0);
}

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
