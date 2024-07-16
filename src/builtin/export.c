/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yushsato <yushsato@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 16:55:11 by nsakanou          #+#    #+#             */
/*   Updated: 2024/07/17 04:24:22 by yushsato         ###   ########.fr       */
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

static int	is_valid_env_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

static int	is_valid_env_str(char *str)
{
	int	i;

	i = 0;
	if (ft_isdigit(*str) || !is_valid_env_char(*str) || *str == '=')
		return (1);
	while (str[++i])
	{
		if (str[i] == '=')
			return (0);
		if (!is_valid_env_char(str[i]))
			return (1);
	}
	return (0);
}

int	bt_export(int argc, char *const *argv, char *const *envp)
{
	int	stat;

	stat = 0;
	(void)envp;
	if (argc < 2)
		export_print_all();
	while (*++argv)
	{
		if (!is_valid_env_str(*argv))
			ENV().set((char **)argv);
		else
		{
			ft_printf("minishell: export: `%s':"
				" not a valid identifier\n", *argv);
			stat = 1;
		}
	}
	return (stat);
}
