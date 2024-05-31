/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yushsato <yushsato@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 00:36:42 by yushsato          #+#    #+#             */
/*   Updated: 2024/05/31 19:33:35 by yushsato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	token_1quote(const char *str, int *i)
{
	int	endable;

	endable = 0;
	while (str[*i] && str[*i] != '\'')
	{
		if (str[*i] == '\\' && str[*i + 1])
			*i += 2;
		if (str[*i] == '\'' && (*i)++ && endable++)
			break ;
		if (str[*i])
			*i += 1;
	}
	return (endable);
}

int	token_2quote(const char *str, int *i)
{
	int	endable;

	endable = 0;
	while (str[*i] && str[*i] != '\"')
	{
		if (str[*i] == '\\' && str[*i + 1])
			*i += 2;
		if (str[*i] == '\"' && (*i)++ && endable++)
			break ;
		if (str[*i])
			*i += 1;
	}
	return (endable);
}

t_token	*token_cutout(const char *str, int len, int type)
{
	t_token	*new;

	new = TKN().new(NULL, len, type);
	new->token = ft_substr(str, 0, len);
	return (new);
}

t_token	*token_conjection(const char *str, int *i)
{
	if (str[*i] == ';')
		return (token_cutout(str, 1, LXR_SCOLON));
	if (!ft_strncmp(&str[*i], "&&", 2))
		return (token_cutout(str, 2, LXR_LOGIC));
	if (str[*i] == '|')
		return (token_cutout(str, 1, LXR_PIPE));
	if (ft_strncmp(&str[*i], ">>", 2))
		return (token_cutout(str, 2, LXR_APPEND));
	if (ft_strncmp(&str[*i], "<<", 2))
		return (token_cutout(str, 2, LXR_HEREDOC));
	if (ft_strncmp(&str[*i], ">", 1))
		return (token_cutout(str, 1, LXR_OUTPUT));
	if (ft_strncmp(&str[*i], "<", 1))
		return (token_cutout(str, 1, LXR_INPUT));
	return (NULL);
}

t_token	*token(const char *str)
{
	int	i;

	i = 0;
	if (str[i] == ';' || ft_strncmp(&str[i], "&&", 2)
		|| str[i] == '|' || str[i] == '>' || str[i] == '<')
		return (token_conjection(str, &i));
	while (str[i] && !ft_isspace(str[i]))
	{
		if (str[i] && str[i] == '\\' && str[i + 1])
			i += 2;
		else if (str[i] == '\'' && token_1quote(str, &i))
			return (NULL);
		else if (str[i] == '\"' && token_2quote(str, &i))
			return (NULL);
		else if (str[i] == ';' || ft_strncmp(&str[i], "&&", 2)
			|| str[i] == '|' || str[i] == '>' || str[i] == '<')
			break ;
		else if (str[i])
			i++;
	}
	return (token_cutout(str, i, LXR_WORD));
}
