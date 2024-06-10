/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yushsato <yushsato@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 19:39:39 by yushsato          #+#    #+#             */
/*   Updated: 2024/06/11 01:15:31 by yushsato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#define CMP ft_memcmp

char	*strallocat(char *dst, const char *add, int len);
int		isenvchar(int c);

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
	char	*envk;
	char	*envv;

	(*src)++;
	while (**src && **src != '\"')
	{
		if ((!CMP(*src, "\\$", 2) || !CMP(*src, "\\\"", 2)) && ++(*src))
			*dst = strallocat(*dst, (*src)++, 1);
		else if (**src == '$' && isenvchar(*(*src + 1)))
		{
			envk = ft_calloc(1, sizeof(char));
			while (isenvchar(*++(*src)))
				envk = strallocat(envk, *src, 1);
			if (ENV().find(envk)
				&& ft_memcpy(&envv, &(ENV().find(envk)->value), sizeof(char *)))
				*dst = strallocat(*dst, envv, ft_strlen(envv));
			free(envk);
		}
		else if (!CMP(*src, "$?", 2) && ++(*src) && ++(*src))
			*dst = strallocat(*dst, ft_itoa(g_signal), 1);
		else
			*dst = strallocat(*dst, (*src)++, 1);
	}
	if (*src)
		(*src)++;
}

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

char	*parse_word(t_token *token)
{
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
		else if (!CMP(src, "$?", 2) && src++)
			dst = strallocat(dst, ft_itoa(g_signal), 1);
		else
			dst = strallocat(dst, src++, 1);
	}
	return (dst);
}
