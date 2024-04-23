/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yushsato <yushsato@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 14:43:52 by yushsato          #+#    #+#             */
/*   Updated: 2024/04/23 22:25:54 by yushsato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_signal = 0;

int	main(int ac, char **av, char **ae)
{
	char	*input;

	(void)av;
	if (ac != 1 && sf_seterrno(EINVAL))
		sf_exit("argv");
	env_set(ae);
	while (1)
	{
		sig_sh(0);
		input = ms_readline();
		ms_isctrld(input);
		
		free(input);
	}
	return (0);
}
