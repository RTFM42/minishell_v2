/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsakanou <nsakanou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 16:40:12 by nsakanou          #+#    #+#             */
/*   Updated: 2024/07/06 16:45:53 by nsakanou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static bool	has_n_option(char *str)
{
	if (str && str[0] == '-' && str[1] == 'n' && str[2] == '\0')
		return (true);
	return (false);
}

int	bt_echo(int argc, char *const *argv, char *const *envp)
{
	size_t	i;

	(void)argc;
	(void)envp;
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
