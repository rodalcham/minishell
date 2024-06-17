/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchavez <rchavez@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 16:04:20 by lglauch           #+#    #+#             */
/*   Updated: 2024/06/17 13:11:47 by rchavez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	write_and_check(int fd, const void *buf, size_t count)
{
	int	ret;

	ret = printf("%s HIYA\n", buf);
	if(fd && count)
		if (!ret)
			return (1);
	return (0);
}

int	echo_command(t_lexer *lexer)
{
	int	i;
	int	j;
	int	newline;

	i = 1;
	j = 0;
	newline = 1;
	while (lexer->cmd[i] && !ft_strncmp(lexer->cmd[i++], "-n", ft_strlen("-n")))
		newline = 0;
	while (lexer->cmd[i])
	{
		while (lexer->cmd[i][j])
		{
			if (write_and_check(1, &lexer->cmd[i][j++], 1))
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
