/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchavez <rchavez@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 16:04:20 by lglauch           #+#    #+#             */
/*   Updated: 2024/06/17 13:34:34 by rchavez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	echo_command(t_lexer *lexer)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	while (lexer->cmd[i] && !ft_strcmp(lexer->cmd[i], "-n"))
		newline = 0;
	while (lexer->cmd[i])
	{
		while (lexer->cmd[i])
		{
			if (write_and_check(1, lexer->cmd[i++], 1))
				return (1);
		}
		if (lexer->cmd[++i])
		{
			if (write_and_check(1, " ", 1))
				return (1);
		}
	}
	if (newline && write_and_check(1, "\n", 1))
		return (1);
	exit (0);
}
