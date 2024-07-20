/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yushsato <yushsato@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 01:17:25 by yushsato          #+#    #+#             */
/*   Updated: 2024/07/21 02:32:34 by yushsato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sig_cache_set(int signo);
int		sig_cache_get(void);

int	g_signal = 0;

/**
 * ## Handles prompt program interruption signals
 * @note	`SIGINT`: Exit with 130, Display prompt on a new line
 * @note	`SIGQUIT`: Nothing to do
 * @param	signo signal number to be passed on in the loop. usually 0 is fine.
 * @return	N/A
*/
void	sig_shell(int signo)
{
	signal(SIGINT, sig_shell);
	signal(SIGQUIT, SIG_IGN);
	if (signo != SIGINT)
		return ;
	rl_on_new_line();
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_redisplay();
	g_signal = 130;
	if (signo)
		sig_cache_set(signo);
}

void	sig_exec(int signo)
{
	signal(SIGINT, sig_exec);
	signal(SIGQUIT, sig_exec);
	if (signo == SIGQUIT)
		ft_printf("Quit: %d\n", signo);
	if (signo != SIGINT)
		return ;
	rl_on_new_line();
	write(1, "\n", 1);
	rl_replace_line("", 0);
	g_signal = 130;
	if (signo)
		sig_cache_set(signo);
}

/**
 * ## Handles heredoc program interruption signals
 * @note	`SIGINT`: Exit with 130, Close fd:`STDIN_FILENO`,
 * 			Display prompt on a new line
 * @note	`SIGQUIT`: Exit with 131, Close fd:`STDIN_FILENO`,
 * 			Display prompt on a new line
 * @param	signo signal number
 * @return	N/A
*/
void	sig_herdoc(int signo)
{
	signal(SIGINT, sig_herdoc);
	signal(SIGQUIT, SIG_IGN);
	if (signo != SIGINT)
		return ;
	sf_close(STDIN_FILENO);
	g_signal = 130;
	if (signo)
		sig_cache_set(signo);
}

/**
 * ## Set `SIGINT` and `SIGQUIT` to default
 * @note	`SIGINT`: Default behavior
 * @note	`SIGQUIT`: Default behavior
 * @return	N/A
*/
void	sig_reset(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

t_sigc	sig_constructor(void)
{
	static const t_sigc	sig = {
		.shell = sig_shell,
		.herdoc = sig_herdoc,
		.exec = sig_exec,
		.reset = sig_reset,
		.set = sig_cache_set,
		.get = sig_cache_get,
	};

	return (sig);
}
