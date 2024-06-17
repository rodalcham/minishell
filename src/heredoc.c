/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchavez <rchavez@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 11:31:18 by rchavez           #+#    #+#             */
/*   Updated: 2024/06/17 13:18:00 by rchavez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	do_heredoc(int fd, char *eof)
{
	int		written;
	char	*line;

	written = 1;
	line = readline("> ");
	while (written > 0 && line && ft_strcmp(line, eof))
	{
		written = write(fd, line, ft_strlen(line));
		if (written < 0 || write(fd, "\n", 1) < 0)
		{
			printf("Heredoc : Failed to write.\n");
			break ;
		}
		free(line);
		line = readline("> ");
	}
	free(line);
	close(fd);
	if (written < 0)
		return (-1);
	return (0);
}
