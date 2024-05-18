/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yushsato <yushsato@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 01:49:38 by yushsato          #+#    #+#             */
/*   Updated: 2024/05/18 15:41:47 by yushsato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
 * ## Generate prompt string
 * @return	Generated prompt string
*/
char	*ms_prompt(void)
{
	char		*prompt;
	const int	len = ft_strlen("minishell");

	prompt = sf_calloc(len + 2 + 1, sizeof(char));
	ft_memcpy(prompt, "minishell", len);
	if (ft_getuid() == 0)
		ft_memcpy(prompt + len, "# ", 2);
	else
		ft_memcpy(prompt + len, "$ ", 2);
	return (prompt);
}
