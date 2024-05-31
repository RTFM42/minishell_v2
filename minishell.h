/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yushsato <yushsato@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 17:07:01 by yushsato          #+#    #+#             */
/*   Updated: 2024/05/31 01:11:48 by yushsato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <signal.h>
# include <unistd.h>
# include <errno.h>
# include <limits.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "lib/libft/libft.h"
# include "lib/printf/ft_printf.h"

# define LXR_WORD 0
# define LXR_PIPE 3
# define LXR_INPUT 4
# define LXR_OUTPUT 5
# define LXR_HEREDOC 6
# define LXR_APPEND 7
# define LXR_LOGIC 8
# define LXR_SCOLON 9
# define LXR_ERROR INT_MAX

extern int	g_signal;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
	struct s_env	*prev;
}	t_env;

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

typedef struct s_token
{
	char			*token;
	int				len;
	int				type;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_tokenc
{
	t_token	*(*new)(char *token, int length, int type);
}	t_tokenc;

typedef struct s_execc
{
	int	(*sync)(char *const *argv, char *const *envp);
	int	(*pipe)(char *const *argv, char *const *envp, int infd, int outfd);
}	t_execc;

typedef struct s_sigc
{
	void	(*shell)(int signo);
	void	(*herdoc)(int signo);
	void	(*ignore)(void);
	void	(*reset)(void);
}	t_sigc;

typedef struct s_parserc
{
	char	**(*parser)(const char *str);
	int		(*run)(char **parsed, char **envp);
	void	(*free)(char **str);
}	t_parserc;

typedef struct s_pathc
{
	char	*(*join)(const char *p1, const char *p2);
	int		(*exists)(const char *path);
	int		(*isfile)(const char *path);
	char	*(*resolve)(const char *bin);
}	t_pathc;

t_envc		env_constructor(void);
t_execc		exec_constructor(void);
t_sigc		sig_constructor(void);
t_parserc	parser_constructor(void);
t_pathc		path_constructor(void);
t_tokenc	token_constructor(void);
t_token		*token(char *str);
t_token		*lexer(char *input);
char		*ms_prompt(void);
char		*ms_readline(void);
void		ms_isctrld(char *stdin);

# define ENV env_constructor
# define EXEC exec_constructor
# define SIG sig_constructor
# define PSR parser_constructor
# define PATH path_constructor
# define TKN token_constructor
#endif
