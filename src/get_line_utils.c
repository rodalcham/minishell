/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchavez <rchavez@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:54:35 by rchavez           #+#    #+#             */
/*   Updated: 2024/07/05 15:55:24 by rchavez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_first_pipe(char *line)
{
	size_t	i;

	i = 0;
	if (!line)
		return (0);
	while (is_spc(line[i]))
		i++;
	if (line[i] == '|')
		return (1);
	return (0);
}

int	is_invalid(char *s)
{
	int	i;
	int	x;

	if (!s || !s[0])
		return (0);
	i = -1;
	x = 0;
	if (is_first_pipe(s))
		return (-2);
	while (s[++i])
	{
		if (is_spc(s[i]))
			continue ;
		if (x > 2 && sep(s[i]) > 2 && !(x == 5 && (s[i] == '<' || s[i] == '>')))
			return (i);
		x = sep(s[i]);
		if ((x == 1 || x == 2) && ++i)
			while (s[i] && x != sep(s[i]))
				i++;
		else if ((x == 3 || x == 4) && x == sep(s[i + 1]))
			i++;
	}
	if (x > 2)
		return (-1);
	return (0);
}

void	say_invalid(char *line, int i)
{
	*get_exit_status() = 2;
	if (!isatty(fileno(stdin)))
		write(2, "bash: line 1: ", 14);
	write(2, "syntax error near unexpected token `", 36);
	if (i == -1)
		write(2, "newline", 7);
	if (i == -2)
		write(2, "|", 1);
	else if ((line[i] == '>' || line[i] == '<') && line[i] == line[i + 1])
		write(2, &line[i], 2);
	else
		write(2, &line[i], 1);
	write(2, "'\n", 2);
	if (!isatty(fileno(stdin)))
	{
		ft_perror("bash: line 1: `", line, "'\n");
		exit(*get_exit_status());
	}
}

char	*rm_nl(char *line)
{
	size_t	i;

	i = 0;
	if (!line)
		return (NULL);
	while (line[i])
		i++;
	if (i && line[i - 1] == '\n')
		line[i - 1] = '\0';
	return (line);
}

char	*take_in(char *in)
{
	char	*line;

	if (isatty(fileno(stdin)))
		return (readline(in));
	else
	{
		line = get_next_line(fileno(stdin));
		line = rm_nl(line);
		return (line);
	}
}
