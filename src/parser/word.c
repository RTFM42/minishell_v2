/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yushsato <yushsato@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 19:39:39 by yushsato          #+#    #+#             */
/*   Updated: 2024/06/19 15:53:40 by yushsato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*strallocat(char *dst, const char *add, int len);
int		isenvchar(int c);

void	parse_env(char **dst, char **src)
{
	char	*envk;
	char	*envv;

	envk = ft_calloc(1, sizeof(char));
	while (isenvchar(*++(*src)))
		envk = strallocat(envk, *src, 1);
	if (ENV().find(envk)
		&& ft_memcpy(&envv, &(ENV().find(envk)->value), sizeof(char *)))
		*dst = strallocat(*dst, envv, ft_strlen(envv));
	free(envk);
}

void	parse_1quote(char **dst, char **src)
{
	char	*rdst;
	char	*rsrc;

	rdst = *dst;
	rsrc = *src;
	while (*(++rsrc) && *rsrc != '\'')
		rdst = strallocat(rdst, rsrc, 1);
	if (*rsrc)
		rsrc++;
	*src = rsrc;
	*dst = rdst;
}

void	parse_2quote(char **dst, char **src)
{
	char	*tmp;

	(*src)++;
	while (**src && **src != '\"')
	{
		if ((!ft_memcmp(*src, "\\$", 2) || !ft_memcmp(*src, "\\\"", 2))
			&& ++(*src))
			*dst = strallocat(*dst, (*src)++, 1);
		else if (**src == '$' && isenvchar(*(*src + 1)))
			parse_env(dst, src);
		else if (!ft_memcmp(*src, "$?", 2) && ++(*src) && ++(*src))
		{
			tmp = ft_itoa(g_signal);
			*dst = strallocat(*dst, tmp, ft_strlen(tmp));
			free(tmp);
		}
		else
			*dst = strallocat(*dst, (*src)++, 1);
	}
	if (*src)
		(*src)++;
}

char	*parse_word(t_token *token)
{
	char		*tmp;
	char		*dst;
	const char	*src = token->token;

	src = token->token;
	dst = ft_calloc(1, sizeof(char));
	while (src && *src)
	{
		if (*src == '\\' && *(src + 1) != '\0' && ++src)
			dst = strallocat(dst, src++, 1);
		else if (*src == '\'')
			parse_1quote(&dst, (char **)&src);
		else if (*src == '\"')
			parse_2quote(&dst, (char **)&src);
		else if (*src == '$' && isenvchar(*(src + 1)))
			parse_env(&dst, (char **)&src);
		else if (!ft_memcmp(src, "$?", 2) && src++ && src++)
		{
			tmp = ft_itoa(g_signal);
			dst = strallocat(dst, tmp, ft_strlen(tmp));
			free(tmp);
		}
		else
			dst = strallocat(dst, src++, 1);
	}
	return (dst);
}
