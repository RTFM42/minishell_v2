/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_cache.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yushsato <yushsato@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 00:39:16 by yushsato          #+#    #+#             */
/*   Updated: 2024/06/19 15:58:16 by yushsato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	*sig_cache(void)
{
	static int	sig = 0;
	
	return (&sig);
}

void	sig_cache_set(int signo)
{
	int	*cache;
	
	cache = sig_cache();
	*cache = signo;
}

int	sig_cache_get(void)
{
	int	*cache;
	
	cache = sig_cache();
	return (*cache);
}
