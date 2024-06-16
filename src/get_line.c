/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchavez <rchavez@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 13:07:56 by rchavez           #+#    #+#             */
/*   Updated: 2024/06/16 14:03:59 by rchavez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_invalid(char *line)
{
	int	i;
	int	op;

	i = -1;
	op = 0;
	if (!line)
		return (0);
	while (line[++i])
	{
		if (is_spc(line[i]))
			continue ;
		if (is_op(line[i]))
		{
			if (op)
				return (i);
			op = 1;
			if ((line[i] == '<' || line[i] == '>') && line[i] == line[i + 1])
				i++;
		}
		else
			op = 0;
	}
	if (op)
		return (-1);
	return (0);
}

void	say_invalid(char *line, int i)
{
	printf("Syntax error near unexpected token '");
	if (i == -1)
		printf("newline");
	else
		printf("%c", line[i]);
	printf("'\n");
}

char	*get_line(void)
{
	char	*line;
	int		inv;

	line = readline("🐚  ");
	inv = is_invalid(line);
	while ((line && !line[0]) || inv)
	{
		free(line);
		if (inv)
			say_invalid(line, inv);
		line = readline("🐚  ");
		inv = is_invalid(line);
	}
	return (line);
}
