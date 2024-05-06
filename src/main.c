/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yushsato <yushsato@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 14:43:52 by yushsato          #+#    #+#             */
/*   Updated: 2024/04/27 12:36:18 by yushsato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_signal = 0;

int	main(int ac, char **av, char **ae)
{
	char	*input;

	(void)av;
	if (ac != 1 && sf_seterrno(EINVAL))
		sf_exit("argv", 1);
	env_set(ae);
	
	
	const char	**raw = envraw_get();
	int		count = 0;
	while (raw[count] != NULL)
	{
		ft_printf("\x1B[32m%s\x1B[0m\n", raw[count]);
		count++;
	}
	
	while (1)
	{
		sig_sh(0);
		input = ms_readline();
		ms_isctrld(input);
		
		free(input);
	}
	exit(1);
}
