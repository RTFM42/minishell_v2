/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsakanou <nsakanou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 18:23:20 by nsakanou          #+#    #+#             */
/*   Updated: 2024/06/22 20:02:04 by nsakanou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"
# include <string.h>
# include <stdlib.h>
# include <errno.h>
# include <ctype.h>

int		exec_builtin(char **argv);

//command
int		echo_command(char **argv);
int		pwd_command(char *init);
int		unset_command(char **argv);
int		exit_command(char **argv);
int		cd_command(char **argv);
int		export_command(char **argv);
int		env_command(void);

//export
char	*export_strjoin(const char *s1, const char *s2);
void	export_sortenvs(t_env *env);
char	*export_getname(char *argv);
char	*export_getvalue(char *argv);
int		export_insert(char *arg, t_env *env);

int		ft_strcmp(const char *s1, const char *s2);

#endif
