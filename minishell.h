/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yushsato <yushsato@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 17:07:01 by yushsato          #+#    #+#             */
/*   Updated: 2024/04/15 04:10:00 by yushsato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <signal.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "lib/libft/libft.h"

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
	struct s_env	*prev;
}	t_env;

extern int	g_signal;

t_env	**env_store(void);
void	env_set(char **list);
t_env	*env_find(char *key);
t_env	*env_push(char *key, char *value);
int		env_delete(char *key);
void	err_invalid_args(void);
char	*ms_prompt(void);
char	*ms_readline(void);
void	ms_isctrld(char *stdin);
void	sig_sh(int signo);
void	sig_hd(int signo);
void	sig_ignore(void);
void	sig_reset(void);
#endif
