/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isenvchar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yushsato <yushsato@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:03:54 by yushsato          #+#    #+#             */
/*   Updated: 2024/07/02 16:04:03 by yushsato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	isenvchar(int c)
{
	if (('0' <= c && c <= '9') || ('a' <= c && c <= 'z')
		|| ('A' <= c && c <= 'Z') || c == '_')
		return (1);
	return (0);
}
