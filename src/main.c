/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yushsato <yushsato@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 14:43:52 by yushsato          #+#    #+#             */
/*   Updated: 2024/06/10 21:33:51 by yushsato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	exit(g_signal);
}

int	main(int ac, char **av, char **ae)
{
	t_token	*token;
	char	*input;
	char	**envp;

	if (av[0] && ac != 1 && ERR().setno(EINVAL))
		(ERR().exit)("argv", 1);
	ENV().set(ae);
	while (1)
	{
		SIG().shell(0);
		input = ms_readline();
		ms_isctrld(input);
		token = PSR().parser(input);
		free(input);
		if (token == NULL)
		{
			g_signal = 2;			
			continue ;
		}
		envp = ENV().dump();
		g_signal = (PSR().run)(token, envp);
		TKN().freeall(token);
		ENV().free(envp);
	}
}
