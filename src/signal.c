/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yushsato <yushsato@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 01:17:25 by yushsato          #+#    #+#             */
/*   Updated: 2024/04/15 01:24:35 by yushsato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
 * ## Handles prompt program interruption signals
 * @note	`SIGINT`: Exit with 130, Display prompt on a new line
 * @note	`SIGQUIT`: Nothing to do
 * @param	signo signal number
 * @return	N/A
*/
void	sig_sh(int signo)
{
	signal(SIGINT, sig_sh);
	signal(SIGQUIT, SIG_IGN);
	if (signo != SIGINT)
		return ;
	rl_on_new_line();
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_redisplay();
	g_signal = 130;
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
void	sig_hd(int signo)
{
	signal(SIGINT, sig_hd);
	signal(SIGQUIT, sig_hd);
	if (signo == SIGINT)
	{
		close(0);
		g_signal = 130;
	}
	else if (signo == SIGQUIT)
	{
		close(0);
		ft_putstr_fd("quit: 3", 1);
		g_signal = 131;
	}
}

/**
 * ## Ignore `SIGINT` and `SIGQUIT`
 * @note	`SIGINT`: Nothing to do
 * @note	`SIGQUIT`: Nothing to do
 * @return	N/A
*/
void	sig_ignore(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
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

/**
 * ## Normal exit if stdin is null 
 * @note 	Pressing "Ctrl+D" causes readline to return null
 * @param	stdin String to be processed in shell
 * @return	N/A
*/
void	ms_isctrld(char *stdin)
{
	if (stdin != NULL)
		return ;
	ft_putstr_fd("exit\n", 1);
	exit(0);
}
