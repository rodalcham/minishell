/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchavez <rchavez@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 13:07:56 by rchavez           #+#    #+#             */
/*   Updated: 2024/06/18 17:28:25 by rchavez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int sep(char c);

int	is_invalid(char *line)
{
	int	i;
	int x;

	if (!line || !line[0])
		return (0);
	i = -1;
	x = 0;
	while (line[++i])
	{
		if (x > 2 && sep(line[i]) > 2)
			return (i);
		x = sep(line[i]);
		if (x == 1 || x == 2)
		{
			i++;
			while (line[i] && x != sep(line[i]))
				i++;
		}
		else if (x == 3 || x == 4)
			if (x == sep(line[i + 1]))
				i++;
	}
	if (x > 2)
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

	line = readline("🐚 ");
	if (!line)
		return (NULL);
	line = handle_unclosed_quotes(line);
	line = expand_tokens(line);
	inv = is_invalid(line);
	while (!line || !line[0] || inv)
	{
		free(line);
		if (inv)
			say_invalid(line, inv);
		line = readline("🐚 ");
		if (!line)
			return (NULL);
		line = handle_unclosed_quotes(line);
		line = expand_tokens(line);
		inv = is_invalid(line);
	}
	return (line);
}
