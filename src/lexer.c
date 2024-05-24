/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yushsato <yushsato@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 00:36:42 by yushsato          #+#    #+#             */
/*   Updated: 2024/05/24 14:20:00 by yushsato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#define LXR_WORD 0
#define LXR_2QUOTE 1
#define LXR_1QUOTE 2
#define LXR_PIPE 3
#define LXR_REDIR 4
#define LXR_SCOLON 5

char	*lexer(const char *str)
{
	
}