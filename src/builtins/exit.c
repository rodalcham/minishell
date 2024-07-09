/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lglauch <lglauch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 11:57:54 by rchavez           #+#    #+#             */
/*   Updated: 2024/07/09 12:30:42 by lglauch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	do_exit(t_lexer *lexer, char **args)
{
	if (args[1] && !args[2] && *get_exit_status() != 255)
		*get_exit_status() = ft_atoi(args[1]);
	while (*get_exit_status() < 0)
		*get_exit_status() = 256 + *get_exit_status();
	if (lexer == *get_lexer() && !lexer->next)
		*get_run() = 0;
	return (*get_exit_status());
}

int	ft_exit(t_lexer *lexer)
{
	int		i;
	char	**args;

	args = lexer->cmd;
	i = -1;
	if (args[1])
	{
		if (args[1][0] == '-' && args[1][1])
			i++;
		while (args[1][++i])
		{
			if (!ft_isdigit(args[1][i]))
			{
				ft_perror("exit: ", args[1], ": numeric argument required\n");
				*get_exit_status() = 255;
				break ;
			}
		}
	}
	if (args[1] && args[2] && *get_exit_status() != 255)
	{
		write(2, "exit: too many arguments\n", 25);
		return (*get_exit_status() = 1);
	}
	return (do_exit(lexer, args));
}
