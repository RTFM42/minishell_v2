/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsakanou <nsakanou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 19:39:39 by yushsato          #+#    #+#             */
/*   Updated: 2024/07/16 00:39:23 by nsakanou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int		isenvchar(int c);
char	*strallocat(char *dst, const char *add, int len);
void	parse_env(t_token *token, char **pdst, char **psrc);

static void	parse_2quote_env(char **pdst, char **psrc)
{
	char	*envk;
	char	*envv;

	if (**psrc == '$' && *(*psrc + 1) == '?' && (*psrc)++ && (*psrc)++)
	{
		envv = ft_itoa(g_signal);
		*pdst = strallocat(*pdst, envv, ft_strlen(envv));
		free(envv);
		return ;
	}
	envk = sf_calloc(1, sizeof(char));
	while (isenvchar(*++(*psrc)))
		envk = strallocat(envk, *psrc, 1);
	if (ENV().find(envk))
	{
		envv = ft_strdup(ENV().find(envk)->value);
		*pdst = strallocat(*pdst, envv, ft_strlen(envv));
		free(envv);
	}
	free(envk);
}

static void	parse_1quote(char **dst, char **src)
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

static void	parse_2quote(char **dst, char **src)
{
	(*src)++;
	while (**src && **src != '\"')
	{
		if ((!ft_memcmp(*src, "\\$", 2) || !ft_memcmp(*src, "\\\"", 2)
				|| !ft_memcmp(*src, "\\\\", 2)) && ++(*src))
			*dst = strallocat(*dst, (*src)++, 1);
		else if (**src == '$'
			&& (isenvchar(*(*src + 1)) || *(*src + 1) == '?'))
			parse_2quote_env(dst, src);
		else
			*dst = strallocat(*dst, (*src)++, 1);
	}
	if (*src)
		(*src)++;
}

void	parse_word(t_token *token)
{
	char	*dst;
	char	*src;

	dst = sf_calloc(1, sizeof(char));
	src = token->token;
	while (src && *src)
	{
		if (*src == '\\' && *(src + 1) != '\0' && ++src)
			dst = strallocat(dst, src++, 1);
		else if (*src == '\'')
			parse_1quote(&dst, &src);
		else if (*src == '\"')
			parse_2quote(&dst, &src);
		else if (*src == '$' && (isenvchar(*(src + 1)) || *(src + 1) == '?'))
			parse_env(token, &dst, &src);
		else
			dst = strallocat(dst, src++, 1);
	}
	free(token->token);
	token->token = dst;
	token->len = ft_strlen(dst);
}
