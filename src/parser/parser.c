/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yushsato <yushsato@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 21:56:34 by yushsato          #+#    #+#             */
/*   Updated: 2024/06/10 19:30:21 by yushsato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*parse_word(t_token *token);
t_token	*sanitize_token(t_token *head);

t_token	*parser(const char *str)
{
	t_token	*token;
	t_token	*thead;
	// t_node	*nhead;

	thead = lexer(str);
	// TKN().printall(thead);
	token = thead;
	while (token)
	{
		if (token->type == LXR_WORD)
			token->token = parse_word(token);
		token = token->next;
	}
	thead = sanitize_token(thead);
	return (thead);
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

int	parser_run(t_token *parsed, char **envp)
{
	int		ret = 0;
	// char	**array;

	/**
	 * # TODO List
	 * 
	 * 1. Token to String Array
	 * 2. Run (exec)
	 */
	// ret = (EXEC().sync)(parsed, envp);
	(void)envp;
	TKN().printall(parsed);
	return (ret);
}

t_parserc	parser_constructor(void)
{
	static const t_parserc	perserc = {
		.parser = parser,
		.run = parser_run,
		.free = parser_free,
	};

	return (perserc);
}
