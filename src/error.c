/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yushsato <yushsato@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 03:51:17 by yushsato          #+#    #+#             */
/*   Updated: 2024/04/15 04:07:52 by yushsato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	err_invalid_args(void)
{
	ft_putstr_fd("minishell: args: Invalid argument\n", 2);
	exit(1);
}
