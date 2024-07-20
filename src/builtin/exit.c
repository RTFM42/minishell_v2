/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsakanou <nsakanou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 16:53:58 by nsakanou          #+#    #+#             */
/*   Updated: 2024/07/18 20:58:22 by nsakanou         ###   ########.fr       */
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

static void	puterr(const char *sh, const char *cmd,
	const char *opt, const char *reason)
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
	ret = ft_strjoin(tmp, opt);
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
		puterr("minishell", "exit", argv[1], "numeric argument required");
		exit(2);
	}
	else if (argc >= 3)
	{
		if (!only_digit(argv[1]))
		{
			ft_putendl_fd("minishell: exit: too many arguments", 2);
			return (1);
		}
		else
		{
			puterr("minishell", "exit", argv[1], "numeric argument required");
			exit(2);
		}
	}
	return (2);
}
