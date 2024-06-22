/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsakanou <nsakanou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 18:23:20 by nsakanou          #+#    #+#             */
/*   Updated: 2024/06/22 16:15:35 by nsakanou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"
# include <string.h>
# include <stdlib.h>
# include <errno.h>
# include <ctype.h>

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}t_env;

int		exec_builtin(char **argv);

//command
int		echo_command(char **argv);
int		pwd_command(char *init);
int		unset_command(char **argv);
int		exit_command(char **argv);
int		cd_command(char **argv);
int		export_command(char **argv);
int		env_command(void);

//env
t_env	*env_search(t_env *env, char *name);
void	env_list_add(t_env **env_list, char *name, char *value);
t_env	*env_create(char **envp);
t_env	**env_store(void);

//env_utils
bool	env_name_judge(char *name);
t_env	*env_del(t_env **env_list, char *name);
void	*env_update(char *name, char *value);
t_env	*lstlast(t_env *lst);

//export
char	check_type(char *str);
void	export_sortenvs(t_env *env);
char	*export_strjoin(const char *s1, const char *s2);
int		export_insert(char *arg, t_env *env);

int		cd_error(void);
void	list_error(void);
int		ft_strcmp(const char *s1, const char *s2);

#endif
