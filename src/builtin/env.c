/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yushsato <yushsato@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 15:52:03 by yushsato          #+#    #+#             */
/*   Updated: 2024/07/25 17:36:00 by yushsato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	bt_env(int argc, char *const *argv, char *const *envp)
{
	char	*res;
	char	*tmp;
	int		i;

	(void)argv;
	if (argc > 1 && ERR().setno(EINVAL) && ERR().print(argv[0]))
		return (1);
	res = sf_calloc(1, sizeof(char));
	i = 0;
	while (envp[i])
	{
		tmp = res;
		res = ft_strjoin(res, envp[i++]);
		free(tmp);
		tmp = res;
		res = ft_strjoin(res, "\n");
		free(tmp);
	}
	ft_putstr_fd(res, STDOUT_FILENO);
	free(res);
	return (0);
}
