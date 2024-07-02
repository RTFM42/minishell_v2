/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yushsato <yushsato@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:43:46 by yushsato          #+#    #+#             */
/*   Updated: 2024/07/02 16:56:34 by yushsato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int		isenvchar(int c);
char	*strallocat(char *dst, const char *add, int len);

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

void	parse_env(t_token *token, char **pdst, char **psrc)
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
