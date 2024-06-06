/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lglauch <lglauch@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 17:51:26 by lglauch           #+#    #+#             */
/*   Updated: 2024/06/06 13:44:59 by lglauch          ###   ########.fr       */
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
	t_lexer	*tokens;
	char	**args;

	line = NULL;
	while (*get_run() == 1)
	{
		line = readline("🐚  ");
		if (!line)
			break ;
		if (line && ft_strlen(line) > 0)
			add_history(line);
		args = ft_split_args(line);
		if (!args)
			printf("Unprotected\n");/////             							    FIX!!!	// XXX: hi
		tokens = tokenize(line, args);
		if (!tokens)
			printf("Error tokens returned NULL");
		int i = 0;
		int j = 0;
        while (i < count_lex(line))
        {
			j = 0;
			printf("\ntoken[%i].path : %s\n", i, tokens[i].path);
			while (tokens[i].cmd[j])
			{
            	printf("\ntoken[%i].cmd[%i] : %s\n", i, j, tokens[i].cmd[j]);
				j++;
			}
			j = 0;
			while (tokens[i].ops[j])
			{
            	printf("\ntoken[%i].ops[%i] : %s\n", i, j, tokens[i].ops[j]);
				j++;
			}
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
	if (argc != 1)
		return (1);
	*get_envp() = ft_create_envp(envp);
	// rl_catch_signals = 0;
	signal_handler();
	intro();
	main_loop();
	printf("exit\n");
	// ft_free_envp(envp_list);
	system("leaks minishell");
	return (0);
}
