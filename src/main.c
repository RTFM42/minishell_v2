/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yushsato <yushsato@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 14:43:52 by yushsato          #+#    #+#             */
/*   Updated: 2024/05/06 23:07:16 by yushsato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_signal = 0;

int	main(int ac, char **av, char **ae)
{
	// char	*input;

	(void)av;
	if (ac != 1 && sf_seterrno(EINVAL))
		sf_exit("argv", 1);
	env_set(ae);
	
	int			count = 0;
	char *const	*raw = envraw_list();

	while (raw[count] != NULL)
	{
		ft_printf("[%d]:", count);	
		ft_printf("\x1B[32m%s\x1B[0m\n", raw[count++]);
	}

	const char	*f = "/usr/bin/find";
	char *const argv[] = {"find", ".", NULL};

	exit(execute_sync(f, argv));
	
	// while (1)
	// {
	// 	sig_sh(0);
	// 	input = ms_readline();
	// 	ms_isctrld(input);
		
	// 	free(input);
	// }
}
