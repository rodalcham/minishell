/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchavez <rchavez@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 17:51:26 by lglauch           #+#    #+#             */
/*   Updated: 2024/07/05 16:24:17 by rchavez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_signal = 0;

void	intro(void)
{
	char	*name;

	name = env_get_by_name("USER");
	if (!isatty(fileno(stdin)))
		return ;
	printf("\033[H\033[J");
	printf("        _   _   _   _   _   _   _   _   _   \n");
	printf("       / \\ / \\ / \\ / \\ / \\ / \\ / \\ / \\ / \\ \n");
	printf("      ( M | I | N | I | S | H | E | L | L )\n");
	printf("       \\_/ \\_/ \\_/ \\_/ \\_/ \\_/ \\_/ \\_/ \\_/ \n");
	printf("         ********************************\n");
	printf("\n    Welcome to Minishell by \033]8;;https://github.com/rodalcham"
		"\archavez\033]8;;\a && \033]8;;https://github.com/lglauch"
		"\alglauch\033]8;;\a\n\n");
	printf("         ********************************\n");
	if (name && name[0])
		printf("\n\t\tWelcome, %s\n", name);
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
		args = ft_split_args(line);
		if (!args)
			free_all(line, args, tokens, -1);
		tokens = lex(args, &status);
		signal(SIGINT, signal_temp);
		if (!status)
			status = execute(tokens);
		signal(SIGINT, handle_ctrlc);
		if (status < 0)
			free_all(line, args, tokens, status);
		free_all(line, args, tokens, 0);
	}
}

static int	shlvl(int value)
{
	if (value < 0)
		return (0);
	else if (value >= 1000)
		return (1);
	else
		return (value);
}

void	make_shlvl(char	**envp)
{
	int		i;
	int		value;
	char	*lvl;
	char	*value_str;
	size_t	lvl_size;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "SHLVL=", ft_strlen("SHLVL=")) == 0)
		{
			value = shlvl(ft_atoi(envp[i] + ft_strlen("SHLVL=")) + 1);
			value_str = ft_itoa(value);
			lvl_size = ft_strlen("SHLVL=") + ft_strlen(value_str) + 1;
			lvl = malloc_t(lvl_size);
			if (lvl)
			{
				ft_strlcpy(lvl, "SHLVL=", lvl_size);
				ft_strlcat(lvl, value_str, lvl_size);
				envp[i] = lvl;
			}
			free_t(value_str);
		}
		i++;
	}
}

int	main(int argc, char **argv, char **envp)
{
	argv = (void *)argv;
	if (argc != 1)
		return (1);
	*ft_env() = init_env(envp);
	if (!(*ft_env()) && envp)
		ft_error(-1);
	make_shlvl(*ft_env());
	signal_handler();
	intro();
	main_loop();
	if (isatty(fileno(stdin)))
		printf("exit\n");
	env_free(*ft_env());
	link_free();
	exit (*get_exit_status());
}
