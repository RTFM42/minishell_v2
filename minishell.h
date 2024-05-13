/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yushsato <yushsato@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 17:07:01 by yushsato          #+#    #+#             */
/*   Updated: 2024/05/13 16:56:50 by yushsato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <signal.h>
# include <unistd.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "lib/libft/libft.h"
# include "lib/printf/ft_printf.h"

extern int	g_signal;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
	struct s_env	*prev;
}	t_env;

typedef struct s_chain
{
	char			*value;
	struct s_chain	*prev;
	struct s_chain	*next;
}	t_chain;
typedef struct s_chainlist
{
	t_chain	*list;
}	t_chainlist;

typedef struct s_envc
{
	t_env	**(*store)(void);
	void	(*set)(char **list);
	t_env	*(*find)(const char *key);
	t_env	*(*push)(const char *key, const char *value);
	int		(*delete)(const char *key);
	char	**(*dump)(void);
	void	(*free)(char **envp);
}	t_envc;

typedef struct s_execc
{
	int	(*sync)(char *const *argv, char *const *envp);
}	t_execc;

t_envc	env_constructor(void);
t_execc	exec_constructor(void);
char	*ms_prompt(void);
char	*ms_readline(void);
void	ms_isctrld(char *stdin);
void	sig_sh(int signo);
void	sig_hd(int signo);
void	sig_ignore(void);
void	sig_reset(void);

# define ENV env_constructor
# define EXEC exec_constructor
#endif
