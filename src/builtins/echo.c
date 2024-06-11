/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lglauch <lglauch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 16:04:20 by lglauch           #+#    #+#             */
/*   Updated: 2024/06/11 14:41:43 by lglauch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// int	write_and_check(int fd, const void *buf, size_t count)
// {
// 	int	ret;

// 	ret = write(fd, buf, count);
// 	if (!ret)
// 		return (1);
// 	return (0);
// }

// int	echo_command(t_lexer *lexer)
// {
// 	int	i;
// 	int	j;
// 	int	newline;

// 	i = 1;
// 	j = 0;
// 	newline = 1;
// 	while (lexer->cmd[i] && !ft_strncmp(lexer->cmd[i++], "-n", ft_strlen("-n")))
// 		newline = 0;
// 	while (lexer->cmd[i])
// 	{
// 		while (lexer->cmd[i][j])
// 		{
// 			if (write_and_check(stdout, &lexer->cmd[i][j++], 1))
// 				return (1);
// 		}
// 		if (lexer->cmd[++i])
// 		{
// 			if (write_and_check(stdout, " ", 1))
// 				return (1);
// 		}
// 	}
// 	if (newline && write_and_check(stdout, "\n", 1))
// 		return (1);
// 	return (0);
// }
