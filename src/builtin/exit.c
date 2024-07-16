/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yushsato <yushsato@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 16:53:58 by nsakanou          #+#    #+#             */
/*   Updated: 2024/07/17 04:47:53 by yushsato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	only_digit(char *str)
{
	if (*str == '-' || *str == '+')
		str++;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (1);
		str++;
	}
	return (0);
}

int	bt_exit(int argc, char *const *argv, char *const *envp)
{
	(void)envp;
	ft_printf("exit\n");
	if (argc == 1)
		exit((256 + g_signal) % 256);
	if (argc == 2)
	{
		if (!only_digit(argv[1]))
			exit((256 + ft_atoi(argv[1])) % 256);
		ft_printf("minishell: exit: %s: numeric argument required\n", argv[1]);
		exit(2);
	}
	else if (argc >= 3)
	{
		if (!only_digit(argv[1]))
			ft_printf("minishell: exit: too many arguments.\n");
		else
		{
			ft_printf("minishell: exit: %s: "
				"numeric argument required\n", argv[1]);
			exit(2);
		}
	}
	return (2);
}
