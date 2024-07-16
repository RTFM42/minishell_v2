/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yushsato <yushsato@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 16:55:11 by nsakanou          #+#    #+#             */
/*   Updated: 2024/07/16 15:53:52 by yushsato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	only_digit(char *str);

static void	export_print_all(void)
{
	char	**envp;
	int		i;

	envp = ENV().dump();
	i = 0;
	while (envp[i])
	{
		printf("declare -x %s\n", envp[i]);
		i++;
	}
	ENV().free(envp);
}

int	bt_export(int argc, char *const *argv, char *const *envp)
{
	int	stat;

	stat = 0;
	(void)envp;
	if (argc < 2)
		export_print_all();
	else if (argv[1][0] == '-' || argv[1][0] == '+')//error status 2にならなければならない
	{
		stat = 2;
		ft_printf("export: '%d': not a valid identifier\n", ft_atoi(argv[1]));
		ft_printf("export: usage: export [-nf] [name[=value] ...] or export -p\n");
	}
	else if (!only_digit(argv[1]) && ++stat)//error status 1
		ft_printf("export: '%d': not a valid identifier\n", ft_atoi(argv[1]));
	else
		ENV().set((char **)&argv[1]);
	return (stat);
}

// bash-3.2$ export -1
// bash: export: -1: invalid option
// export: usage: export [-nf] [name[=value] ...] or export -p
// bash-3.2$ echo $?
// 2
// bash-3.2$ export 1
// bash: export: `1': not a valid identifier
// bash-3.2$ echo $?
// 1