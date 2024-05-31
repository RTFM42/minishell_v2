/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yushsato <yushsato@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 03:22:27 by yushsato          #+#    #+#             */
/*   Updated: 2024/05/26 01:34:49 by yushsato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
 * ## Extended readline to able to follow history
 * @return	stdin string
*/
char	*ms_readline(void)
{
	char	*prompt;
	char	*input;
	char	*extra;
	char	*tmp;

	prompt = ms_prompt();
	input = readline(prompt);
	free(prompt);
	while (input && *input && input[ft_strlen(input) - 1] == '\\'
		&& !(ft_strlen(input) >= 2 && input[ft_strlen(input) - 2] == '\\'))
	{
		tmp = input;
		extra = readline("> ");
		input[ft_strlen(input) - 1] = '\0';
		input = ft_strjoin(input, extra);
		free(tmp);
		free(extra);
	}
	if (input && input[0] != '\0')
		add_history(input);
	return (input);
}
