/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yushsato <yushsato@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 21:56:34 by yushsato          #+#    #+#             */
/*   Updated: 2024/06/11 02:04:57 by yushsato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*parse_word(t_token *token);
t_token	*sanitize_token(t_token *head);

t_token	*parser(const char *str)
{
	t_token	*token;
	t_token	*head;

	head = lexer(str);
	token = head;
	while (token)
	{
		if (token->type == LXR_WORD)
			token->token = parse_word(token);
		token = token->next;
	}
	head = sanitize_token(head);
	token = head;
	while (token)
	{
		if (token->type == LXR_ERROR)
		{
			TKN().freeall(head);
			return (NULL);
		}
		token = token->next;
	}
	return (head);
}

void	parser_free(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		free(args[i++]);
	free(args[i]);
	free(args);
}

t_parserc	parser_constructor(void)
{
	static const t_parserc	perserc = {
		.parser = parser,
		.free = parser_free,
	};

	return (perserc);
}
