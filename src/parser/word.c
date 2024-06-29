/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yushsato <yushsato@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 19:39:39 by yushsato          #+#    #+#             */
/*   Updated: 2024/06/29 17:52:35 by yushsato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*strallocat(char *dst, const char *add, int len);

int	isenvchar(int c)
{
	if (('0' <= c && c <= '9') || ('a' <= c && c <= 'z')
		|| ('A' <= c && c <= 'Z') || c == '_')
		return (1);
	return (0);
}

static void	parse_2quote_env(char **pdst, char **psrc)
{
	char	*envk;
	char	*envv;

	if (**psrc != '$' && *(*psrc + 1) == '?' && (*psrc)++ && (*psrc)++)
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
		else if (**src == '$')
			parse_2quote_env(dst, src);
		else
			*dst = strallocat(*dst, (*src)++, 1);
	}
	if (*src)
		(*src)++;
}

static void	deploy_env_signal(char **pdst)
{
	char	*envv;

	envv = ft_itoa(g_signal);
	*pdst = strallocat(*pdst, envv, ft_strlen(envv));
	free(envv);
}

static void	deploy_env(char **split, t_token *token, char **pdst)
{
	int		i;
	int		j;
	t_token	*prev;
	t_token	*next;

	i = 0;
	while (split && split[i])
		i++;
	if (i == 0)
		return ;
	else if (i == 1)
		*pdst = strallocat(*pdst, split[0], ft_strlen(split[0]));
	else if (i >= 2)
	{
		*pdst = strallocat(*pdst, split[0], ft_strlen(split[0]));
		prev = TKN().new(*pdst, ft_strlen(*pdst), LXR_WORD);
		prev->next = token;
		prev->prev = token->prev;
		token->prev = prev;
		if (prev->prev)
			prev->prev->next = prev;
		j = 1;
		while (j < i - 1)
		{
			next = TKN().new(ft_strdup(split[j]), ft_strlen(split[j]), LXR_WORD);
			next->next = token;
			next->prev = prev;
			prev->next = next;
			token->prev = next;
			prev = next;
			j++;
		}
		*pdst = ft_strdup(split[i - 1]);
	}
}

static void	parse_env(t_token *token, char **pdst, char **psrc)
{
	char	*envk;
	char	*envv;
	char	**split;
	int		i;

	if (!ft_memcmp(*psrc, "$?", 2) && (*psrc)++ && (*psrc)++)
		deploy_env_signal(pdst);
	else if (**psrc == '$')
	{
		envk = sf_calloc(1, sizeof(char));
		while (isenvchar(*++(*psrc)))
			envk = strallocat(envk, *psrc, 1);
		if (ENV().find(envk))
		{
			envv = ft_strdup(ENV().find(envk)->value);
			split = ft_split(envv, ' ');
			deploy_env(split, token, pdst);
			i = 0;
			while (split && split[i])
				free(split[i++]);
			free(split);
		}
	}
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
