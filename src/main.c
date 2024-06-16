/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchavez <rchavez@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 17:51:26 by lglauch           #+#    #+#             */
/*   Updated: 2024/06/16 14:46:45 by rchavez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	intro(void)
{
	if (!isatty(fileno(stdin)))
		return ;
	printf("\033[H\033[J");
	printf("   _   _   _   _   _   _   _   _   _   \n");
	printf("  / \\ / \\ / \\ / \\ / \\ / \\ / \\ / \\ / \\ \n");
	printf(" ( M | I | N | I | S | H | E | L | L )\n");
	printf("  \\_/ \\_/ \\_/ \\_/ \\_/ \\_/ \\_/ \\_/ \\_/ \n");
	printf("    ********************************\n");
	printf("\n    Welcome to Minishell by \033]8;;https://github.com/rodalcham"
		"\archavez\033]8;;\a && \033]8;;https://github.com/lglauch"
		"\alglauch\033]8;;\a\n\n");
	printf("    ********************************\n");
}

void	main_loop(void)
{
	static char		*line;
	static t_lexer	*tokens;
	static char		**args;
	int				status;

	while (*get_run() == 1)
	{
		status = 0;
		line = get_line();
		if (!line)
			break ;
		if (line && ft_strlen(line) > 0)
			add_history(line);
		args = ft_split_args(line);
		if (!args)
			free_all(line, args, tokens, -1);
		tokens = lex(args, &status);
		if (!status)
			status = execute(tokens);
		if (status < 0)
			free_all(line, args, tokens, status);
		free_all(line, args, tokens, 0);
	}
}

int	main(int argc, char **argv, char **envp)
{
	argv = (void *)argv;
	if (argc != 1)
		return (1);
	*get_envp() = ft_create_envp(envp);
	init_env(envp);
	// rl_catch_signals = 0;
	signal_handler();
	intro();
	main_loop();
	printf("exit\n");
	ft_free_envp(*get_envp());
	system("leaks minishell");
	return (0);
}
