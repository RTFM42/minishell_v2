/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yushsato <yushsato@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 16:54:27 by nsakanou          #+#    #+#             */
/*   Updated: 2024/07/13 18:32:59 by yushsato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	bt_pwd(int argc, char *const *argv, char *const *envp)
{
	char	*pwd;
	int		status;

	status = 0;
	if (argc > 1 && ERR().setno(EINVAL) && ERR().print(argv[0]) && ++status)
		return (status);
	pwd = sf_calloc(1, PATH_MAX);
	if (getcwd(pwd, PATH_MAX) != NULL)
		ft_printf("%s\n", pwd);
	else if (ERR().print("pwd"))
		++status;
	free(pwd);
	return (status);
}
