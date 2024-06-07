/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yushsato <yushsato@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 21:56:34 by yushsato          #+#    #+#             */
/*   Updated: 2024/06/08 00:09:07 by yushsato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
int	word(char *str);

char	**parser(const char *str)
{
	char	**ret;
	t_token	*token;
	
	token = lexer(str);
	TKN().printall(token);
	TKN().freeall(token);
	ret = ft_split(str, ' ');
	return (ret);
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

int	run(char **parsed, char **envp)
{
	// int	pipefd[2];
	int		ret;

	// char	*ls[] = {"ls", NULL};
	// char	*cat[] = {"cat", NULL};

	// (void)parsed;
	// pipe(pipefd);
	// (EXEC().pipe)((char *const *)ls, envp, 0, pipefd[1]);
	// ret = EXEC().pipe((char *const *)cat, envp, pipefd[0], 1);
	// close(pipefd[0]);
	// close(pipefd[1]);
	
	ret = (EXEC().sync)(parsed, envp);
	return (ret);
}

t_parserc	parser_constructor(void)
{
	static const t_parserc	perserc = {
		.parser = parser,
		.run = run,
		.free = parser_free,
	};

	return (perserc);
}
