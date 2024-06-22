/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsakanou <nsakanou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 17:52:50 by nsakanou          #+#    #+#             */
/*   Updated: 2024/06/22 18:17:48 by nsakanou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static bool	has_n_option(char *str)
{
	if (str && str[0] == '-' && str[1] == 'n' && str[2] == '\0')
		return (true);
	return (false);
}

int	echo_command(char **argv)
{
	size_t	i;

	i = 1;
	while (has_n_option(argv[i]))
		i++;
	while (argv[i])
	{
		printf("%s", argv[i]);
		if (argv[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (!has_n_option(argv[1]))
		printf("\n");
	return (0);
}
