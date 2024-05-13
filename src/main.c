/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yushsato <yushsato@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 14:43:52 by yushsato          #+#    #+#             */
/*   Updated: 2024/05/10 18:19:30 by yushsato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_signal = 0;

int	main(int ac, char **av, char **ae)
{
	const t_envc	envc = env_constructor();
	const t_execc	execc = exec_constructor();

	(void)av;
	if (ac != 1 && sf_seterrno(EINVAL))
		sf_exit("argv", 1);
	envc.set(ae);

	char *const argv[] = {"/opt/homebrew/bin/bash", NULL};
	char **envp = envc.dump();
	int exits = execc.sync(argv, envp);
	envc.free(envp);
	exit(exits);
	
	// while (1)
	// {
	// 	sig_sh(0);
	// 	input = ms_readline();
	// 	ms_isctrld(input);
	// 	free(input);
	// }
}
