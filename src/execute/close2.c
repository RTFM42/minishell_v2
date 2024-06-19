/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yushsato <yushsato@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 17:20:39 by yushsato          #+#    #+#             */
/*   Updated: 2024/06/19 17:22:39 by yushsato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	close_pipe(int *pipe)
{
	const int	err1 = sf_close(pipe[0]);
	const int	err2 = sf_close(pipe[1]);

	if (err1 < 0)
		sf_error_print("close");
	if (err2 < 0)
		sf_error_print("close");
}

