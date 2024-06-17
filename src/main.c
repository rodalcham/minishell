/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lglauch <lglauch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 17:51:26 by lglauch           #+#    #+#             */
/*   Updated: 2024/06/17 16:34:45 by lglauch          ###   ########.fr       */
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
		if(!ft_strncmp(line, "exit ", 5))
			return (free(line));
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

void	make_shlvl(char	**envp)
{
	int		i;
	int		j;
	int		value;
	char	*lvl;

	i = 0;
	j = 0;
	value = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "SHLVL=", ft_strlen("SHLVL=")) == 0)
		{
			value = ft_atoi(envp[i] + ft_strlen("SHLVL="));
			value++;
			lvl = malloc(sizeof(char) * 6 + ft_strlen(ft_itoa(value)));
			ft_strlcat(lvl, "SHLVL=", 6);
			ft_strlcat(lvl, ft_itoa(value), ft_strlen(ft_itoa(value)) + 1);
			ft_strlcat(lvl, "\n", 1);
			envp[i] = lvl;
		}
		i++;
	}
}

int	main(int argc, char **argv, char **envp)
{
	argv = (void *)argv;
	if (argc != 1)
		return (1);
	*get_envp() = ft_create_envp(envp);
	if (!*get_envp())
		ft_error(-1);
	init_env(envp);
	make_shlvl(envp);
	// rl_catch_signals = 0;
	signal_handler();
	intro();
	main_loop();
	printf("exit\n");
	ft_free_envp(*get_envp());
	// system("leaks minishell");
	return (*get_exit_status());
}
