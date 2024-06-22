/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_name_value.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsakanou <nsakanou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 19:54:24 by nsakanou          #+#    #+#             */
/*   Updated: 2024/06/22 19:57:18 by nsakanou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

char	*export_getname(char *argv)
{
	int		i;
	char	*name;

	i = -1;
	if (!argv[0])
		return (NULL);
	while (argv[++i])
	{
		if ((!env_name_judge(argv) || (argv[i] == ' ' && argv[i + 1] == '='))
			&& ERR().print("export"))
			return (NULL);
		if (argv[i] == '=' || (argv[i] == '+' && argv[i + 1] == '='))
		{
			name = ft_calloc(i + 1, sizeof(char));
			ft_strlcpy(name, argv, i + 1);
			return (name);
		}
	}
	name = ft_calloc(i + 1, sizeof(char));
	ft_strlcpy(name, argv, i + 1);
	return (name);
}

char	*export_getvalue(char *argv)
{
	char	*value;
	char	*equal;

	equal = ft_strchr(argv, '=');
	if (equal == NULL)
		return (NULL);
	value = ft_strdup(equal + 1);
	return (value);
}
