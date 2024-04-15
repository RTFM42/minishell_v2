/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yushsato <yushsato@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 03:22:27 by yushsato          #+#    #+#             */
/*   Updated: 2024/04/14 22:23:38 by yushsato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
 * ## Extended readline to able to follow history
 * @return	stdin string
*/
char	*ms_readline(void)
{
	char	*input;
	char	*prompt;

	prompt = ms_prompt();
	input = readline(prompt);
	free(prompt);
	if (input && input[0] != '\0')
		add_history(input);
	return (input);
}
