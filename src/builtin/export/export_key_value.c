/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_key_value.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsakanou <nsakanou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 16:42:01 by nsakanou          #+#    #+#             */
/*   Updated: 2024/06/26 16:53:50 by nsakanou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

char	*get_key(const char *argv)
{
	char	*key;
	char	*key_end;
	size_t	len;

	key_end = ft_strchr(argv, '=');
	if (!key_end)
		return (ft_strdup(argv));
	len = key_end - argv;
	key = ft_calloc(len, sizeof(char));
	ft_strlcpy(key, argv, len);
	return (key);
}

char	*get_value(const char *argv)
{
	char	*key_end;
	char	*value;

	key_end = ft_strchr(argv, '=');
	if (!key_end)
		return (NULL);
	value = ft_strdup(key_end + 1);
	return (value);
}
