/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsakanou <nsakanou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 16:55:11 by nsakanou          #+#    #+#             */
/*   Updated: 2024/07/22 01:17:41 by nsakanou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int		only_digit(char *str);

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
	ret = ft_strjoin(tmp, ": `");
	free(tmp);
	tmp = ret;
	ret = ft_strjoin(tmp, opt);
	free(tmp);
	tmp = ret;
	ret = ft_strjoin(tmp, "': ");
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

static void	export_print_all(void)
{
	t_env	*env;

	env = *(ENV().store());
	while (env)
	{
		if (env->value)
			ft_printf("declare -x %s=\"%s\"\n", env->key, env->value);
		else
			ft_printf("declare -x %s\n", env->key);
		env = env->next;
	}
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
	int		stat;

	stat = 0;
	(void)envp;
	if (argc < 2)
		export_print_all();
	while (*++argv)
	{
		if (!is_valid_env_str(*argv))
		{
			if (!(ft_strchr(*argv, '=') == NULL && ENV().find(*argv) != NULL))
				ENV().set((char **)argv);
		}
		else
		{
			puterr("minishell", "export", *argv, "not a valid identifier");
			stat = 1;
		}
	}
	return (stat);
}
