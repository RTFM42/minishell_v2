/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsakanou <nsakanou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 18:23:20 by nsakanou          #+#    #+#             */
/*   Updated: 2024/06/26 17:05:58 by nsakanou         ###   ########.fr       */
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
char	*get_key(const char *argv);
char	*get_value(const char *argv);
int		env_name_judge(const char *key);

int		ft_strcmp(const char *s1, const char *s2);

#endif
