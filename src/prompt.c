/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yushsato <yushsato@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 01:49:38 by yushsato          #+#    #+#             */
/*   Updated: 2024/05/18 15:49:47 by yushsato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
 * ## Generate prompt string
 * @return	Generated prompt string
*/
char	*ms_prompt(void)
{
	t_env		*env;
	char		*prompt;
	const int	len = ft_strlen("minishell");

	env = ENV().find("USER");
	prompt = sf_calloc(len + 2 + 1, sizeof(char));
	ft_memcpy(prompt, "minishell", len);
	if (env && !ft_strncmp(env->value, "root", 5))
		ft_memcpy(prompt + len, "# ", 2);
	else
		ft_memcpy(prompt + len, "$ ", 2);
	return (prompt);
}
