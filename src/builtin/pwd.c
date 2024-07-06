/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsakanou <nsakanou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 16:54:27 by nsakanou          #+#    #+#             */
/*   Updated: 2024/07/06 16:56:40 by nsakanou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	bt_pwd(int argc, char *const *argv, char *const *envp)
{
	char		*pwd;
	static char	*save;
	char		*tmp;

	pwd = ft_calloc(1, PATH_MAX);
	if (argv)
		save = ft_strdup(argv);
	else if (getcwd(pwd, PATH_MAX) != NULL)
	{
		tmp = save;
		save = ft_strdup(pwd);
		printf("%s\n", pwd);
		if (!tmp)
			free(tmp);
	}
	else if (!printf("%s\n", save))
	{
		free(pwd);
		return (1);
	}
	free (pwd);
	return (0);
}
