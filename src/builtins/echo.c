/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchavez <rchavez@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 16:04:20 by lglauch           #+#    #+#             */
/*   Updated: 2024/07/08 11:43:37 by rchavez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// int	echo_command(t_lexer *lexer)
// {
// 	int	i;
// 	int	newline;

// 	i = 1;
// 	newline = 1;
// 	if (lexer->cmd[i] && !ft_strcmp(lexer->cmd[i], "-n"))
// 	{
// 		newline = 0;
// 		i++;
// 	}
// 	while (lexer->cmd[i])
// 	{
// 		while (lexer->cmd[i])
// 		{
// 			if (printf("%s", lexer->cmd[i++]) == -1)
// 				return (1);
// 			if (lexer->cmd[i])
// 			{
// 				if (printf(" ") == -1)
// 					return (1);
// 			}
// 		}
// 	}
// 	if (newline && printf("\n"))
// 		return (0);
// 	return (0);
// }

int	is_n_flag(char *str)
{
	size_t	i;

	i = 0;
	if (!str || str[0] != '-')
		return (0);
	i++;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	echo_command(t_lexer *lexer)
{
	int		i;
	int		newline;
	char	**cmd;

	i = 1;
	newline = 1;
	cmd = lexer->cmd;
	while (cmd[i] && is_n_flag(cmd[i]))
	{
		newline = 0;
		i++;
	}
	while (cmd[i])
	{
		printf("%s", cmd[i]);
		if (cmd[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
	return (0);
}
