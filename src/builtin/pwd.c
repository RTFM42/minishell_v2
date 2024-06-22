/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsakanou <nsakanou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 17:53:15 by nsakanou          #+#    #+#             */
/*   Updated: 2024/06/22 18:25:10 by nsakanou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	pwd_command(char *init)
{
	char		*pwd;
	static char	*save;
	char		*tmp;

	pwd = ft_calloc(1, PATH_MAX);
	if (init)
		save = ft_strdup(init);
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
