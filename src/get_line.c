/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchavez <rchavez@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 13:07:56 by rchavez           #+#    #+#             */
/*   Updated: 2024/07/05 16:23:56 by rchavez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		is_invalid(char *s);
void	say_invalid(char *line, int i);

char	*take_line(int *inv)
{
	char	*line;

	line = take_in("🐚 ");
	if (!line)
		return (NULL);
	line = handle_unclosed_quotes(line);
	if (line && ft_strlen(line) > 0)
		add_history(line);
	line = expand_tokens(line, 0);
	if (!line)
		return (NULL);
	*inv = is_invalid(line);
	return (line);
}

char	*get_line(void)
{
	char	*line;
	int		inv;

	inv = 0;
	line = take_line(&inv);
	if (!line)
		return (NULL);
	while (!line || !line[0] || inv)
	{
		if (inv)
			say_invalid(line, inv);
		free_t(line);
		line = take_line(&inv);
		if (!line)
			return (NULL);
	}
	return (line);
}
