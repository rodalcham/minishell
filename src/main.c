/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchavez@student.42heilbronn.de <rchavez    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 17:51:26 by lglauch           #+#    #+#             */
/*   Updated: 2024/05/22 14:59:23 by rchavez@stu      ###   ########.fr       */
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
	char	*line;
	char	**args;
	t_lexer	*tokens;

	line = NULL;
	while (*get_run() == 1)
	{
		line = readline("🐚  ");
		if (line == NULL)
		{
			write(1, "\r🐚  exit", ft_strlen("\r🐚  exit"));
			//free because of ctrl + D
			if (line)
				free(line);
			exit (0);
		}
		if (line && ft_strlen(line) > 0)
			add_history(line);
		args = ft_split_args(line);
		if (!args)
			printf("\nProtection Missing\n");// 											FIX!
		tokens = tokenize(line, args);
		if (!tokens)
			printf("Error tokens returned NULL");
		int i = 0;
		int j;
        while (i < count_lex(line))
        {
			j = -1;
            while (tokens[i].cmd[++j])
				printf("\nToken %i, command %i: %s\n", i, j, tokens[i].cmd[j]);
			j = -1;
            while (tokens[i].ops[++j])
				printf("\nToken %i, operator %i: %s\n", i, j, tokens[i].ops[j]);
			printf("\nToken %i, path: %s\n", i, tokens[i].path);
            i++;
        }
		if (ft_strncmp(line, "exit", 4) == 0 && line[4] == 0)
		{
			free_tokens(tokens, args, line);
			break ;
		}
		free_tokens(tokens, args, line);
	}
}

int	main(int argc, char **argv, char **envp)
{
	argv = (void *)argv;
	envp = (void *)envp;
	if (argc != 1)
		return (1);
	// rl_catch_signals = 0;
	// signal_handler();
	intro();
	main_loop();
	printf("exit\n");
	system("leaks minishell");
	return (0);
}
