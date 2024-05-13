/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yushsato <yushsato@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 14:43:52 by yushsato          #+#    #+#             */
/*   Updated: 2024/05/13 16:43:35 by yushsato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_signal = 0;

int	main(int ac, char **av, char **ae)
{
	(void)av;
	if (ac != 1 && sf_seterrno(EINVAL))
		sf_exit("argv", 1);
	ENV().set(ae);

	char *const argv[] = {"/opt/homebrew/bin/bash", NULL};
	char **envp = ENV().dump();
	int exits = EXEC().sync(argv, envp);
	ENV().free(envp);
	exit(exits);
	
	// while (1)
	// {
	// 	sig_sh(0);
	// 	input = ms_readline();
	// 	ms_isctrld(input);
	// 	free(input);
	// }
}
