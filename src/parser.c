/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yushsato <yushsato@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 21:56:34 by yushsato          #+#    #+#             */
/*   Updated: 2024/05/31 19:21:13 by yushsato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
int	word(char *str);

char	**parser(const char *str)
{
	char	**ret;
	t_token	*token;
	
	token = lexer(str);
	while (token)
	{
		ft_printf("%s, ", token->token);
		if (token->type == LXR_WORD)
			ft_printf("%s\n", "WORD");
		else if (token->type == LXR_PIPE)
			ft_printf("%s\n", "PIPE");
		else if (token->type == LXR_INPUT)
			ft_printf("%s\n", "INPUT");
		else if (token->type == LXR_OUTPUT)
			ft_printf("%s\n", "OUTPUT");
		else if (token->type == LXR_HEREDOC)
			ft_printf("%s\n", "HEREDOC");
		else if (token->type == LXR_APPEND)
			ft_printf("%s\n", "APPEND");
		else if (token->type == LXR_LOGIC)
			ft_printf("%s\n", "LOGIC");
		else if (token->type == LXR_SCOLON)
			ft_printf("%s\n", "SCOLON");
		else
			ft_printf("%s\n", "ERROR");
		token = token->next;
	}

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
