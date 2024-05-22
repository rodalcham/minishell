/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leo <leo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 17:51:26 by lglauch           #+#    #+#             */
/*   Updated: 2024/05/22 15:31:42 by leo              ###   ########.fr       */
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
	printf("\n    Welcome to Minishell by \033]8;;https://github.com/lglauch"
		"\alglauch\033]8;;\a && ...\n\n");
	printf("    ********************************\n");
}

void	main_loop(void)
{
	char	*line;
	char	**tokens;

	line = NULL;
	while (*get_run() == 1)
	{
		line = readline("🐚  ");
		if (!line)
			break ;
		if (line && ft_strlen(line) > 0)
			add_history(line);
		tokens = ft_split_args(line);
		if (!tokens)
			printf("Error tokens returned NULL");
		int i = 0;
        while (tokens[i] != NULL)
        {
            printf("tokens[%d] = %s\n", i, tokens[i]); //delete later just a tester
            i++;
        }
		if (ft_strncmp(line, "exit", 4) == 0 && line[4] == 0)
		{
			free (line);
			break ;
		}
	}
	if (line)
		free(line);
}

int	main(int argc, char **argv, char **envp)
{
	argv = (void *)argv;
	envp = (void *)envp;
	if (argc != 1)
		return (1);
	rl_attempted_completion_function = my_completion_function;
	rl_catch_signals = 0;
	signal_handler();
	intro();
	main_loop();
	printf("exit\n");
	return (0);
}
