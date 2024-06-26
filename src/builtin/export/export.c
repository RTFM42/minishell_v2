/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsakanou <nsakanou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 16:33:02 by nsakanou          #+#    #+#             */
/*   Updated: 2024/06/26 17:12:28 by nsakanou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	export_print_all(void)
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

int	export_command(char **argv)
{
	int		i;
	char	*key;
	char	*value;

	if (!argv[1])
	{
		export_print_all();
		return (0);
	}
	i = 1;
	while (argv[i])
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
