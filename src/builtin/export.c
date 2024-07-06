/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsakanou <nsakanou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 16:55:11 by nsakanou          #+#    #+#             */
/*   Updated: 2024/07/06 17:33:55 by nsakanou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*get_key(const char *argv)
{
	char	*key;
	char	*key_end;
	size_t	len;

	key_end = ft_strchr(argv, '=');
	if (!key_end)
		return (ft_strdup(argv));
	len = key_end - argv;
	key = ft_calloc(len, sizeof(char));
	ft_strlcpy(key, argv, len);
	return (key);
}

static char	*get_value(const char *argv)
{
	char	*key_end;
	char	*value;

	key_end = ft_strchr(argv, '=');
	if (!key_end)
		return (NULL);
	value = ft_strdup(key_end + 1);
	return (value);
}

static int	env_name_judge(const char *key)
{
	const char	*ptr = key;

	if (!key || !ft_isalpha(key[0]))
		return (0);
	while (*ptr)
	{
		if (!ft_isalnum(*ptr) && *ptr != '_')
			return (0);
		ptr++;
	}
	return (1);
}

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
	int		i;
	char	*key;
	char	*value;

	(void)envp;
	if (argc < 2)
	{
		export_print_all();
		return (0);
	}
	i = 1;
	while (i < argc)
	{
		key = get_key(argv[i]);
		value = get_value(argv[i]);
		if (env_name_judge(key))
		{
			if (ENV().push(key, value) == NULL)
				ERR().print("export");
		}
		else
			ERR().print("export");
		free(key);
		free(value);
		i++;
	}
	return (0);
}
