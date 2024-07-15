/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsakanou <nsakanou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 17:07:01 by yushsato          #+#    #+#             */
/*   Updated: 2024/07/15 18:42:10 by nsakanou         ###   ########.fr       */
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
# include <stdbool.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "lib/libft/libft.h"
# include "lib/printf/ft_printf.h"

# define LXR_WORD 0
# define LXR_INPUT 1
# define LXR_HEREDOC 2
# define LXR_OUTPUT 3
# define LXR_APPEND 4
# define LXR_PIPE 5
# define LXR_LOGIC 6
# define LXR_SCOLON 7
# define LXR_ERROR INT_MAX

# define PSR_NORMAL 0
# define PSR_1QUOTE 1
# define PSR_2QUOTE 2

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
	void	(*init)(void);
	t_env	**(*store)(void);
	void	(*set)(char **list);
	t_env	*(*find)(const char *key);
	t_env	*(*push)(const char *key, const char *value);
	int		(*delete)(const char *key);
	char	**(*dump)(void);
	char	**(*redump)(void);
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
	t_token	*(*new)(char *token, int len, int type);
	int		(*iserror)(t_token *token);
	void	(*freeall)(t_token *head);
}	t_tokenc;

typedef struct s_node
{
	int				conjection_type;
	int				exit_status;
	int				cancel;
	char			**args;
	t_token			*in_tokens;
	t_token			*out_tokens;
	struct s_node	*next;
	struct s_node	*prev;
}	t_node;

typedef struct s_nodec
{
	t_node	*(*free)(t_node *node);
	t_node	*(*new)(t_node *prev);
	t_token	*(*add_args)(t_node *target, t_token *cursor);
	t_token	*(*add_redir)(t_node *target, t_token *cursor);
}	t_nodec;

typedef struct s_io
{
	int		type;
	int		pipe[2];
	char	**info;
}	t_io;

typedef struct s_execc
{
	pid_t	(*async)(char *const *argv, char *const *envp, int *ifp, int *ofp);
	int		(*await)(pid_t pid);
	int		(*promise_all)(void);
	void	(*promise_add)(pid_t pid);
	int		(*run)(t_token *head, char **envp);
}	t_execc;

typedef struct s_sigc
{
	void	(*shell)(int signo);
	void	(*herdoc)(int signo);
	void	(*exec)(int signo);
	void	(*reset)(void);
	void	(*set)(int signo);
	int		(*get)(void);
}	t_sigc;

typedef struct s_parserc
{
	t_token	*(*parser)(const char *str);
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
t_token		*lexer(const char *input);
t_nodec		node_constructor(void);
char		*ms_prompt(void);
char		*ms_readline(void);
void		ms_isctrld(char *stdin);

# define ENV env_constructor
# define EXEC exec_constructor
# define SIG sig_constructor
# define PSR parser_constructor
# define PATH path_constructor
# define TKN token_constructor
# define NODE node_constructor
#endif
