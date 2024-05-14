/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yushsato <yushsato@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 14:43:52 by yushsato          #+#    #+#             */
/*   Updated: 2024/05/14 08:05:13 by yushsato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_signal = 0;

/**
 * ## Normal exit if stdin is null 
 * @note 	Pressing "Ctrl+D" causes readline to return null
 * @param	stdin String to be processed in shell
 * @return	N/A
*/
void	ms_isctrld(char *stdin)
{
	if (stdin != NULL)
		return ;
	ft_putstr_fd("exit\n", 1);
	exit(0);
}

int	main(int ac, char **av, char **ae)
{
	char	*input;

	if (av[0] && ac != 1 && ERR().setno(EINVAL))
		(ERR().exit)("argv", 1);
	ENV().set(ae);
	char *const argv[] = {"/opt/homebrew/bin/bash", NULL};
	char **envp = ENV().dump();
	int exits = EXEC().sync(argv, envp);
	ENV().free(envp);
	// exit(exits);
	(void)exits;
	
	while (1)
	{
		SIG().shell(0);
		input = ms_readline();
		ms_isctrld(input);
		free(input);
	}
}
