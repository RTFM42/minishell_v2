/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_name_judge.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsakanou <nsakanou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:01:23 by nsakanou          #+#    #+#             */
/*   Updated: 2024/06/26 17:05:41 by nsakanou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	env_name_judge(const char *key)
{
	const char	*ptr = key;

	if (!key || !ft_isalpha(key[0]))
		return (0);
	while (*ptr)
	{
		if (!ft_isalnum(*ptr) && *ptr != '_')
			return (0);
		ptr++;
	}
	return (1);
}
