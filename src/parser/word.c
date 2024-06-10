/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yushsato <yushsato@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 19:39:39 by yushsato          #+#    #+#             */
/*   Updated: 2024/06/10 22:20:56 by yushsato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#define CMP ft_memcmp

int	isenvchar(int c)
{
	if (('0' <= c && c <= '9') || ('a' <= c && c <= 'z')
		|| ('A' <= c && c <= 'Z') || c == '_')
		return (1);
	return (0);
}

char	*stralocat(char *dst, const char *add, int len)
{
	int		dlen;
	char	*ret;

	dlen = ft_strlen(dst);
	ret = ft_calloc(dlen + len + 1, sizeof(char));
	ft_memcpy(ret, dst, dlen);
	ft_memcpy(ret + dlen, add, len);
	free(dst);
	return (ret);
}

void	parse_1quote(char **dst, char **src)
{
	char	*rdst;
	char	*rsrc;

	rdst = *dst;
	rsrc = *src;
	while (*(++rsrc) && *rsrc != '\'')
		rdst = stralocat(rdst, rsrc, 1);
	if (*rsrc)
		rsrc++;
	*src = rsrc;
	*dst = rdst;
}

void	parse_2quote(char **dst, char **src)
{
	char	*envk;
	char	*envv;

	(*src)++;
	while (**src && **src != '\"')
	{
		if ((!CMP(*src, "\\$", 2) || !CMP(*src, "\\\"", 2)) && ++(*src))
			*dst = stralocat(*dst, (*src)++, 1);
		else if (**src == '$' && isenvchar(*(*src + 1)))
		{
			envk = ft_calloc(1, sizeof(char));
			while (isenvchar(*++(*src)))
				envk = stralocat(envk, *src, 1);
			if (ENV().find(envk)
				&& ft_memcpy(&envv, &(ENV().find(envk)->value), sizeof(char *)))
				*dst = stralocat(*dst, envv, ft_strlen(envv));
			free(envk);
		}
		else if (**src == '$' && (*(*src + 1)) == '?' && ++(*src) && ++(*src))
			*dst = stralocat(*dst, ft_itoa(g_signal), 1);
		else
			*dst = stralocat(*dst, (*src)++, 1);
	}
	if (*src)
		(*src)++;
}

char	*parse_word(t_token *token)
{
	char		*dst;
	const char	*src = token->token;

	src = token->token;
	dst = ft_calloc(1, sizeof(char));
	while (src && *src)
	{
		if (*src == '\\' && *(src + 1) != '\0' && ++src)
			dst = stralocat(dst, src++, 1);
		else if (*src == '\'')
			parse_1quote(&dst, (char **)&src);
		else if (*src == '\"')
			parse_2quote(&dst, (char **)&src);
		else
			dst = stralocat(dst, src++, 1);
	}
	return (dst);
}
