/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lglauch <lglauch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 16:04:20 by lglauch           #+#    #+#             */
/*   Updated: 2024/06/17 16:43:43 by lglauch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	echo_command(t_lexer *lexer)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	if (lexer->cmd[i] && !ft_strcmp(lexer->cmd[i], "-n"))
	{
		newline = 0;
		i++;
	}
	while (lexer->cmd[i])
	{
		while (lexer->cmd[i])
		{
			if (printf("%s", lexer->cmd[i++]) == -1)
				return (1);
			if (lexer->cmd[i])
			{
				if (printf(" ") == -1)
					return (1);
			}
		}
	}
	if (newline && printf("\n"))
		return (0);
	return (0);
}
