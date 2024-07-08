/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsakanou <nsakanou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 16:53:58 by nsakanou          #+#    #+#             */
/*   Updated: 2024/07/08 23:02:33 by nsakanou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	only_digit(char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (1);
		str++;
	}
	return (0);
}

static int	num_of_argc(char **argv)
{
	int	argc;
	int	i;

	i = 1;
	argc = 0;
	if (argv[i + 1])
	{
		while (argv[argc + 1])
			argc++;
	}
	return (argc);
}

static void	can_exit(char **argv)
{
	int	argc;

	argc = num_of_argc(argv);
	if (argc == 0)
		return ;
	if (argc > 1)
		ERR().exit("exit", 1);
	if (!only_digit(argv[1]))
		ERR().exit("exit", 255);
}

int	bt_exit(int argc, char *const *argv, char *const *envp)
{
	t_env	*def;

	can_exit(argv);
	def = ENV().find;
	if (def == NULL)
		exit (0);
	exit(ft_atoi(def->value));
	ERR().exit("exit", 1);
	return (1);
}
