/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yushsato <yushsato@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:34:31 by yushsato          #+#    #+#             */
/*   Updated: 2024/05/14 17:39:05 by yushsato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*path_join(const char *p1, const char *p2)
{
	char	*dir;
	char	*ret;

	if (p1 && p2 && ft_strlen(p1) > 0 && ft_strlen(p2) > 0)
	{
		if (p1[ft_strlen(p1) - 1] != '/')
			dir = ft_strjoin(p1, "/");
		else
			dir = ft_strdup(p1);
		if (ft_strlen(p2) >= 2 && p2[0] == '.' && p2[1] == '/')
			ret = ft_strjoin(dir, p2 + 2);
		else if (ft_strlen(p2) >= 1 && p2[0] == '/')
			ret = ft_strjoin(dir, p2 + 1);
		else
			ret = ft_strjoin(dir, p2);
		free(dir);
		return (ret);
	}
	else if (p1 && ft_strlen(p1) > 0)
		return (ft_strdup(p1));
	else if (p2 && ft_strlen(p2) > 0)
		return (ft_strdup(p2));
	return (NULL);
}

int	path_exists(const char *path)
{
	struct stat	pstat;

	if (stat(path, &pstat) == 0)
		return (1);
	return (0);
}

int	path_isfile(const char *path)
{
	struct stat	pstat;

	if (stat(path, &pstat) == 0)
	{
		if (S_ISDIR(pstat.st_mode))
			return (0);
		else
			return (1);
	}
	return (0);
}

char	*path_resolve(const char *bin)
{
	char	**envs;
	char	*path;
	int		count;

	if (bin && ft_strchr(bin, '/')
		&& (!ENV().find("PATH") || !ENV().find("PATH")->value))
		return (ft_strdup(bin));
	envs = ft_split(ENV().find("PATH")->value, ':');
	count = -1;
	while (envs[++count])
	{
		path = path_join(envs[count], bin);
		if (path_exists(path) && path_isfile(path))
			return (path);
		free(path);
	}
	return (ft_strdup(bin));
}

t_pathc	path_constructor(void)
{
	static const t_pathc	path = {
		.exists = path_exists,
		.isfile = path_isfile,
		.join = path_join,
		.resolve = path_resolve,
	};

	return (path);
}
